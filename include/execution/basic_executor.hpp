#pragma once
#include <utility>
#include <type_traits>

namespace execution {
	template <typename ExecutorBranch, typename ExecutorTraits>
	class basic_executor
	{
	public:
		typedef			 ExecutorBranch			          branch_type;
		typedef			 ExecutorTraits				      traits_type;
		
		typedef typename ExecutorTraits::running_branch   execution_handle;
		typedef typename ExecutorTraits::suspended_branch suspended_handle;
		typedef typename ExecutorTraits::state_type       state_type ; // State of the Execution.

	public:
		template <typename ExecType, typename... ExecArgs>
		execution_handle execute      (ExecType&&, ExecArgs&&...);
		state_type		 execute_state(execution_handle&);
		suspended_handle suspend	  (execution_handle&);
		
		void			 run		  ()				 { __M_executor_traits.current()(); }
		void			 run_next     ()				 { __M_executor_traits.next   ()(); }

	private:
		traits_type __M_executor_traits;
	};
}

template <typename ExecutorBranch, typename ExecutorTraits>
template <typename ExecType, typename... ExecArgs>
execution::basic_executor<ExecutorBranch, ExecutorTraits>::execution_handle
	execution::basic_executor<ExecutorBranch, ExecutorTraits>::execute(ExecType&& exec, ExecArgs&&... args)
{
	return __M_executor_traits.start(exec, std::forward<ExecArgs>(args)...);
}

template <typename ExecutorBranch, typename ExecutorTraits>
execution::basic_executor<ExecutorBranch, ExecutorTraits>::suspended_handle
	execution::basic_executor<ExecutorBranch, ExecutorTraits>::suspend(execution_handle& exec)
{
	return __M_executor_traits.suspend(exec);
}

template <typename ExecutorBranch, typename ExecutorTraits>
execution::basic_executor<ExecutorBranch, ExecutorTraits>::state_type  
	execution::basic_executor<ExecutorBranch, ExecutorTraits>::execute_state(execution_handle& hnd)
{
	return hnd.state();
}