#pragma once
#include <type_traits>
#include <execution/trigger/category.hpp>
#include <execution/execution_type.hpp>

#define EXECUTOR_RUN_TRIGGER(trig, args) if(trig) trig(args); 
namespace execution {
	template <typename ExecutorBranch, typename ExecutorTraits>
	class basic_executor
	{
	public:
		typedef			 ExecutorBranch			    branch_type;
		typedef			 ExecutorTraits				traits_type;
		
		typedef typename ExecutorTraits::running    running;
		typedef typename ExecutorTraits::suspended  suspended;

	public:
		template <typename ExecType, typename... ExecArgs>
		running    dispatch(ExecType&&, ExecArgs&&...);
		template <typename DispatchType, typename ExecType, typename... ExecArgs>
		running    dispatch(DispatchType&&, running&, ExecType&&, ExecArgs&&...);

		suspended  suspend (running&)				  ;
		running    resume  (suspended&)				  ;
		void	   execute ()						  ;

	public:
		template <typename Trigger, typename Action>
		void trigger_if(Trigger&&, Action&&) {  }

		template <typename Trigger, typename Action>
		void trigger_if(Trigger&&, Action&&) requires std::is_same_v<std::decay_t<Trigger>, trigger::on_resumed>  ;

		template <typename Trigger, typename Action>
		void trigger_if(Trigger&&, Action&&) requires std::is_same_v<std::decay_t<Trigger>, trigger::on_suspended>;

	private:
		traits_type __M_executor_traits;

	private:
		std::function<void(running&)>   __M_executor_onResumed  ;
		std::function<void(suspended&)> __M_executor_onSuspended;
	};
}

template <typename ExecutorBranch, typename ExecutorTraits>
template <typename ExecType, typename... ExecArgs>
execution::basic_executor<ExecutorBranch, ExecutorTraits>::running
	execution::basic_executor<ExecutorBranch, ExecutorTraits>::dispatch(ExecType&& exec, ExecArgs&&... args)
{
	return __M_executor_traits.dispatch(exec, std::forward<ExecArgs>(args)...);
}

template <typename ExecutorBranch, typename ExecutorTraits>
template <typename DispatchType, typename ExecType, typename... ExecArgs>
execution::basic_executor<ExecutorBranch, ExecutorTraits>::running
	execution::basic_executor<ExecutorBranch, ExecutorTraits>::dispatch(DispatchType&& type, running& hnd, ExecType&& exec, ExecArgs&&... args)
{
	return __M_executor_traits.dispatch(type, hnd, exec, std::forward<ExecArgs>(args)...);
}

template <typename ExecutorBranch, typename ExecutorTraits>
execution::basic_executor<ExecutorBranch, ExecutorTraits>::suspended
	execution::basic_executor<ExecutorBranch, ExecutorTraits>::suspend(running& exec)
{
	auto   hnd_suspend = __M_executor_traits.suspend	 (exec);
	EXECUTOR_RUN_TRIGGER(__M_executor_onSuspended, hnd_suspend);
						 
	return hnd_suspend;
}

template <typename ExecutorBranch, typename ExecutorTraits>
execution::basic_executor<ExecutorBranch, ExecutorTraits>::running
	execution::basic_executor<ExecutorBranch, ExecutorTraits>::resume(suspended& exec)
{
	auto   hnd_resume =  __M_executor_traits.resume   (exec);
	EXECUTOR_RUN_TRIGGER(__M_executor_onResumed, hnd_resume);

	return hnd_resume;
}

template <typename ExecutorBranch, typename ExecutorTraits>
void execution::basic_executor<ExecutorBranch, ExecutorTraits>::execute()
{
	__M_executor_traits.execute();
}

template <typename ExecutorBranch, typename ExecutorTraits>
template <typename Trigger, typename Action>
void execution::basic_executor<ExecutorBranch, ExecutorTraits>::trigger_if(Trigger&&, Action&& action) requires std::is_same_v<std::decay_t<Trigger>, trigger::on_resumed>
{
	__M_executor_onResumed   = action;
}

template <typename ExecutorBranch, typename ExecutorTraits>
template <typename Trigger, typename Action>
void execution::basic_executor<ExecutorBranch, ExecutorTraits>::trigger_if(Trigger&&, Action&& action) requires std::is_same_v<std::decay_t<Trigger>, trigger::on_suspended>
{
	__M_executor_onSuspended = action;
}