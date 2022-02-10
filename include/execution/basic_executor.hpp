#pragma once
#include <utility>
#include <type_traits>

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
		suspended  suspend (running&);
		running    resume  (suspended&);
		void	   execute ();

	private:
		traits_type __M_executor_traits;
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
execution::basic_executor<ExecutorBranch, ExecutorTraits>::suspended
	execution::basic_executor<ExecutorBranch, ExecutorTraits>::suspend(running& exec)
{
	return __M_executor_traits.suspend(exec);
}

template <typename ExecutorBranch, typename ExecutorTraits>
execution::basic_executor<ExecutorBranch, ExecutorTraits>::running
	execution::basic_executor<ExecutorBranch, ExecutorTraits>::resume(suspended& exec)
{
	return __M_executor_traits.resume(exec);
}

template <typename ExecutorBranch, typename ExecutorTraits>
void execution::basic_executor<ExecutorBranch, ExecutorTraits>::execute()
{
	__M_executor_traits.execute();
}