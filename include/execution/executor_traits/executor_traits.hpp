#pragma once
#include <execution/forward.hpp>

#include <mutex>
#include <iostream>

namespace execution {
	template <typename ExecutorBranch, typename ExecutorQueue>
	class executor_traits
	{
	public:
		typedef			 std::remove_pointer_t<ExecutorBranch> branch_type;
		typedef			 ExecutorQueue::queue_type			   queue_type ;
		typedef typename ExecutorQueue::queue_iterator		   handle_type;

		class			 running  ;
		class			 suspended;

	public:
		executor_traits () : __M_traits_rq_current(__M_traits_rq.begin()) {  }
		~executor_traits()												  {  }

	public:
		template <typename ExecType, typename... ExecArgs>
		running   dispatch(ExecType&&, ExecArgs&&...);
		suspended suspend (running&);
		running   resume  (suspended&);
		void      execute ();

	private:
		queue_type  __M_traits_rq, __M_traits_sq;
		handle_type __M_traits_rq_current;
	};

	template <typename ExecutorBranch, typename ExecutorQueue>
	class executor_traits<ExecutorBranch, ExecutorQueue>::running
	{
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
		friend class executor_traits<ExecutorBranch, ExecutorQueue>;

		typedef executor_traits<ExecutorBranch, ExecutorQueue> traits_type;
		typedef traits_type::handle_type					   handle_type;

		suspended(handle_type hnd) : __M_sq_handle(hnd) {  }
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
	return suspended(__M_traits_rq.migrate(rq.__M_rq_handle, __M_traits_sq));
}

template <typename ExecutorBranch, typename ExecutorQueue>
execution::executor_traits<ExecutorBranch, ExecutorQueue>::running execution::executor_traits<ExecutorBranch, ExecutorQueue>::resume(suspended& sq)
{
	return running(__M_traits_sq.migrate(sq.__M_sq_handle, __M_traits_rq));
}

template <typename ExecutorBranch, typename ExecutorQueue>
void execution::executor_traits<ExecutorBranch, ExecutorQueue>::execute()
{
	(*++__M_traits_rq_current)();
}