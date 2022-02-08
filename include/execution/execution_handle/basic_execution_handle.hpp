#pragma once

namespace execution {
	template <typename ExecutionTrait>
	class basic_execution_handle
	{
	public:
		typedef			 ExecutionTrait				  trait_type;
		typedef typename ExecutionTrait::context_type context_type;

	public:
		class status
		{
			template <typename T>
			friend class basic_execution_handle;

			template <typename T>
			friend class execution_traits;

			template <typename T, typename U, typename V>
			friend class basic_execution_branch;
		
		public:
			enum   class execution_state : std::uint8_t									  { standby, running, ended };
			status (basic_execution_handle<ExecutionTrait>& hnd) : __M_status_handle(hnd) { hnd.__M_handle_state				   = execution_state::running; }
			~status()																	  {		__M_status_handle.__M_handle_state = execution_state::ended  ; }

		public:
			bool operator==(execution_state s) { return (__M_status_handle.__M_handle_state == s); }
			bool operator!=(execution_state s) { return (__M_status_handle.__M_handle_state != s); }

		private:
			basic_execution_handle<ExecutionTrait>& __M_status_handle;
		};

	public:
		basic_execution_handle(context_type& prev, context_type& curr) : __M_handle_pairred(prev),
																		 __M_handle_curr   (curr),
																		 __M_handle_state  (status::execution_state::standby) {  }
		void yield()							
		{
								  __M_handle_state = status::execution_state::standby;
			trait_type::switch_to(__M_handle_curr, __M_handle_pairred);
		}

	private:
		status::execution_state __M_handle_state  ;
		context_type&			__M_handle_pairred,
			        &			__M_handle_curr   ;
	};
}

