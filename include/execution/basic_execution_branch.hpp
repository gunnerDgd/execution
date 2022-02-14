#pragma once
#include <context/basic_context.hpp>
#include <context/forward.hpp>

#include <execution/traits/execution_traits.hpp>
#include <execution/execution_handle/basic_execution_handle.hpp>

#include <execution/execution_status.hpp>
#include <execution/trigger/category.hpp>

#define EXECUTE_TRIGGER(trig, argument) if(trig) trig(argument);

namespace execution {
	template <typename BranchContext, typename BranchTrait, typename BranchHandle>
	class basic_execution_branch
	{
	public:
		typedef		     BranchHandle													  branch_handle ;
		typedef			 BranchContext													  branch_context;
		typedef			 BranchTrait													  branch_trait  ;
		typedef			 basic_execution_branch<BranchContext, BranchTrait, BranchHandle> this_type     ;

	public:
		template <typename ExecType, typename... ExecArgs>
		basic_execution_branch (ExecType&&, ExecArgs&&...);
		~basic_execution_branch();

	public:
		void			operator()() {		  branch_trait ::switch_to(__M_branch_context, __M_branch_context_pairred); }
		execution_state state	  () { return						   __M_branch_status; }

	public:
		template <typename TriggerCategory, typename TriggerAction>
		void trigger_if(TriggerCategory&&, TriggerAction&&) {  }

		template <typename TriggerCategory, typename TriggerAction>
		void trigger_if(TriggerCategory&&, TriggerAction&&) requires std::is_same_v<std::decay_t<TriggerCategory>, trigger::on_executed>;

		template <typename TriggerCategory, typename TriggerAction>
		void trigger_if(TriggerCategory&&, TriggerAction&&) requires std::is_same_v<std::decay_t<TriggerCategory>, trigger::on_yielded> ;

		template <typename TriggerCategory, typename TriggerAction>
		void trigger_if(TriggerCategory&&, TriggerAction&&) requires std::is_same_v<std::decay_t<TriggerCategory>, trigger::on_stopped> ;

	private:
		branch_context  __M_branch_context,		    // Current Branch Information.
					    __M_branch_context_pairred; // Executed Branch Information
		execution_state __M_branch_status;

	private:
		std::function<void(this_type&)> __M_branch_onExecuted,
										__M_branch_onYielded ,
										__M_branch_onStopped ;
	};
}

template <typename BranchContext, typename BranchTrait, typename BranchHandle>
template <typename ExecType, typename... ExecArgs>
execution::basic_execution_branch<BranchContext, BranchTrait, BranchHandle>::basic_execution_branch(ExecType&& exec, ExecArgs&&... args) : __M_branch_context_pairred(4096 * 4),
																																		   __M_branch_handle		 (__M_branch_context, __M_branch_context_pairred),
																																		   __M_branch_status		 (execution_state::standby)
{
	auto exec_pack = branch_trait::to_pack					(__M_branch_context, __M_branch_context_pairred, __M_branch_status, exec, std::forward<ExecArgs>(args)...);
					 branch_trait::execute_at<branch_handle>(exec_pack);
}

template <typename BranchContext, typename BranchTrait, typename BranchHandle>
execution::basic_execution_branch<BranchContext, BranchTrait, BranchHandle>::~basic_execution_branch()
{	
	while (!(__M_branch_status & execution_state::ended))
		branch_trait::switch_to(__M_branch_context, __M_branch_context_pairred);
}

template <typename BranchContext, typename BranchTrait, typename BranchHandle>
template <typename TriggerCategory, typename TriggerAction>
void execution::basic_execution_branch<BranchContext, BranchTrait, BranchHandle>::trigger_if(TriggerCategory&&, TriggerAction&& action) requires std::is_same_v<std::decay_t<TriggerCategory>, execution::trigger::on_executed>
{
	__M_branch_onExecuted = action;
}

template <typename BranchContext, typename BranchTrait, typename BranchHandle>
template <typename TriggerCategory, typename TriggerAction>
void execution::basic_execution_branch<BranchContext, BranchTrait, BranchHandle>::trigger_if(TriggerCategory&&, TriggerAction&& action) requires std::is_same_v<std::decay_t<TriggerCategory>, execution::trigger::on_yielded>
{
	__M_branch_onYielded  = action;
}

template <typename BranchContext, typename BranchTrait, typename BranchHandle>
template <typename TriggerCategory, typename TriggerAction>
void execution::basic_execution_branch<BranchContext, BranchTrait, BranchHandle>::trigger_if(TriggerCategory&&, TriggerAction&& action) requires std::is_same_v<std::decay_t<TriggerCategory>, execution::trigger::on_stopped>
{
	__M_branch_onStopped  = action;
}

template <typename BranchContext, typename BranchTrait, typename BranchHandle>
void execution::basic_execution_branch<BranchContext, BranchTrait, BranchHandle>::operator()()
{
	EXECUTE_TRIGGER		   (__M_branch_onExecuted, *this);
	branch_trait::switch_to(__M_branch_context   , __M_branch_context_pairred);

	if (__M_branch_status & execution_state::ended) EXECUTE_TRIGGER(__M_branch_onStopped, *this);
	else											EXECUTE_TRIGGER(__M_branch_onYielded, *this);
}