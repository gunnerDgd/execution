#pragma once
#include <execution/execution_status.hpp>
#include <execution/trigger/category.hpp>

namespace execution {
	template <typename ExecutionTrait>
	class basic_execution_handle
	{
	public:
		typedef			 ExecutionTrait				  trait_type  ;
		typedef typename ExecutionTrait::context_type context_type;
		typedef		     execution_state			  status_type ;

	public:
		basic_execution_handle (context_type& prev, context_type& curr, execution_state& state) : __M_handle_pairred(prev),
																								  __M_handle_curr   (curr),
																								  __M_handle_state  (state) { __M_handle_state = execution_state::running; }
		~basic_execution_handle()																							{ __M_handle_state = execution_state::ended  ; }
		
		void yield	   ();
		
	private:
		execution_state& __M_handle_state  ;
		context_type   & __M_handle_pairred, &__M_handle_curr   ;

	private:
		typedef std::function<void()>
	};
} 

template <typename ExecutionTrait>
void execution::basic_execution_handle<ExecutionTrait>::yield()
{
						  __M_handle_state |= execution_state::yielded;
	trait_type::switch_to(__M_handle_curr, __M_handle_pairred);
						  __M_handle_state ^= execution_state::running;
}