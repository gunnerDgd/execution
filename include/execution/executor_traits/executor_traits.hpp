#pragma once
#include <execution/trigger/trigger.hpp>

#include <mutex>
#include <iostream>

namespace execution {
	template <typename ExecutorBranch, typename ExecutorQueue>
	class executor_traits
	{
	public:
		typedef			 executor_traits<ExecutorBranch, ExecutorQueue> traits_type;
		typedef			 std::remove_pointer_t<ExecutorBranch>			branch_type;
		typedef			 ExecutorQueue::queue_type						queue_type ;
		typedef typename ExecutorQueue::queue_iterator					handle_type;

		class			 running  ;
		class			 suspended;
		class			 trigger_set;

	public:
		executor_traits () : __M_traits_rq_current(__M_traits_rq.begin()) {  }
		~executor_traits()												  {  }

	public:
		template <typename ExecType, typename... ExecArgs>
		running   dispatch(ExecType&&, ExecArgs&&...);
		suspended suspend (running&);
		running   resume  (suspended&);
		void      execute ();

	public:
		template <typename T, typename Action>
		void register_trigger(Action&& act)											       {  }
		template <typename T, typename Action>
		void register_trigger(Action&& act) requires std::is_same_v<T, trigger::executed>  { onExecuted  = act; }
		template <typename T, typename Action>
		void register_trigger(Action&& act) requires std::is_same_v<T, trigger::resumed>   { onResumed   = act; }
		template <typename T, typename Action>
		void register_trigger(Action&& act) requires std::is_same_v<T, trigger::yielded>   { onYielded   = act; }
		template <typename T, typename Action>
		void register_trigger(Action&& act) requires std::is_same_v<T, trigger::suspended> { onSuspended = act; }

	private:
		queue_type  __M_traits_rq, __M_traits_sq;
		handle_type __M_traits_rq_current;

		basic_trigger<trigger::executed , traits_type> onExecuted ;
		basic_trigger<trigger::resumed  , traits_type> onResumed  ;
		basic_trigger<trigger::yielded  , traits_type> onYielded  ;
		basic_trigger<trigger::suspended, traits_type> onSuspended;
	};

	template <typename ExecutorBranch, typename ExecutorQueue>
	class executor_traits<ExecutorBranch, ExecutorQueue>::running
	{
		template <typename T, typename U>
		friend class basic_executor;
		friend class executor_traits<ExecutorBranch, ExecutorQueue>;

		typedef executor_traits<ExecutorBranch, ExecutorQueue> traits_type;
		typedef traits_type::handle_type					   handle_type;

		running(handle_type hnd) : __M_rq_handle(hnd) {  }

	private:
		handle_type __M_rq_handle;
	};
	
	template <typename ExecutorBranch, typename ExecutorQueue>
	class executor_traits<ExecutorBranch, ExecutorQueue>::suspended
	{
		template <typename T, typename U>
		friend class basic_executor;
		friend class executor_traits<ExecutorBranch, ExecutorQueue>;

		typedef executor_traits<ExecutorBranch, ExecutorQueue> traits_type;
		typedef traits_type::handle_type					   handle_type;

		suspended(handle_type hnd)  : __M_sq_handle(hnd) {  }

	private:
		handle_type __M_sq_handle;
	};
}

template <typename ExecutorBranch, typename ExecutorQueue>
template <typename ExecType, typename... ExecArgs>
execution::executor_traits<ExecutorBranch, ExecutorQueue>::running execution::executor_traits<ExecutorBranch, ExecutorQueue>::dispatch(ExecType&& exec, ExecArgs&&... args)
{
	return running(__M_traits_rq.enqueue(new branch(exec, std::forward<ExecArgs>(args)...)));
}

template <typename ExecutorBranch, typename ExecutorQueue>
execution::executor_traits<ExecutorBranch, ExecutorQueue>::suspended execution::executor_traits<ExecutorBranch, ExecutorQueue>::suspend(running& rq)
{
	suspended   sq_handle = suspended(__M_traits_rq.migrate(rq.__M_rq_handle, __M_traits_sq));
	onSuspended(sq_handle);

	return      sq_handle;
}

template <typename ExecutorBranch, typename ExecutorQueue>
execution::executor_traits<ExecutorBranch, ExecutorQueue>::running execution::executor_traits<ExecutorBranch, ExecutorQueue>::resume(suspended& sq)
{
	running   rq_handle = running(__M_traits_sq.migrate(sq.__M_sq_handle, __M_traits_rq));
	onResumed(rq_handle);
	
	return    rq_handle;
}

template <typename ExecutorBranch, typename ExecutorQueue>
void execution::executor_traits<ExecutorBranch, ExecutorQueue>::execute()
{
	++				   __M_traits_rq_current;
	onExecuted(running(__M_traits_rq_current));
	
				 	 (*__M_traits_rq_current)();
	onYielded (running(__M_traits_rq_current));
}