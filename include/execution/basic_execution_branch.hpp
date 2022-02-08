#pragma once
#include <context/basic_context.hpp>
#include <context/forward.hpp>

#include <execution/traits/execution_traits.hpp>
#include <execution/execution_handle/basic_execution_handle.hpp>

namespace execution {
	template <typename BranchContext, typename BranchTrait, typename BranchHandle>
	class basic_execution_branch
	{
	public:
		typedef		     BranchHandle													  branch_handle ;
		typedef			 BranchContext													  branch_context;
		typedef			 BranchTrait													  branch_trait  ;
		typedef			 basic_execution_branch<BranchContext, BranchTrait, BranchHandle> this_type;

	public:
		template <typename ExecType, typename... ExecArgs>
		basic_execution_branch (this_type&, ExecType&&, ExecArgs&&...);
		basic_execution_branch ()									  {  }
		~basic_execution_branch();

	public:
		void operator()() { branch_trait::switch_to(__M_branch_parent.__M_branch_context, __M_branch_context); }

	private:
		branch_context __M_branch_context;
		branch_handle  __M_branch_handle ;
		this_type&	   __M_branch_parent ;

	};
}

template <typename BranchContext, typename BranchTrait, typename BranchHandle>
template <typename ExecType, typename... ExecArgs>
execution::basic_execution_branch<BranchContext, BranchTrait, BranchHandle>::basic_execution_branch(this_type& prev, ExecType&& exec, ExecArgs&&... args) : __M_branch_parent(prev),
																																						    __M_branch_handle(prev, __M_branch_context)
{
	auto exec_pack = branch_trait::to_pack   (__M_branch_context, prev.__M_branch_context, exec, __M_branch_handle, std::forward<ExecArgs>(args)...);
					 branch_trait::execute_at(exec_pack);
}

template <typename BranchContext, typename BranchTrait, typename BranchHandle>
execution::basic_execution_branch<BranchContext, BranchTrait, BranchHandle>::~basic_execution_branch()
{
	typename branch_handle::status status(__M_branch_handle);
	
	while (status != branch_handle::status::execution_state::ended)
		branch_trait::switch_to(__M_branch_parent.__M_branch_context, __M_branch_context);
}