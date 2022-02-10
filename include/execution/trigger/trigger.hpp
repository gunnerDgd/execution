#pragma once
#include <execution/trigger/category.hpp>

namespace execution {
	template <typename Category, typename Executor>
	class basic_trigger;

	template <typename Executor>
	class basic_trigger<trigger::executed, Executor>
	{
	public:
		typedef Executor		    executor;
		typedef Executor::running   running;
		typedef Executor::suspended suspended;
		
		typedef void			 (*type)(running);

		basic_trigger() : __M_trigger_exec(nullptr) {  }
	public:
		void operator= (type    tr) {					    __M_trigger_exec = tr; }
		void operator()(running rq) { if (__M_trigger_exec) __M_trigger_exec(rq) ; }

	private:
		type __M_trigger_exec;
	};

	template <typename Executor>
	class basic_trigger<trigger::resumed, Executor>
	{
	public:
		typedef Executor		    executor;
		typedef Executor::running   running;
		typedef Executor::suspended suspended;

		typedef void			 (*type)(running);

		basic_trigger() : __M_trigger_exec(nullptr) {  }
	public:
		void operator= (type    tr) {					   __M_trigger_exec = tr; }
		void operator()(running rq) { if(__M_trigger_exec) __M_trigger_exec(rq) ; }

	private:
		type __M_trigger_exec;
	};

	template <typename Executor>
	class basic_trigger<trigger::suspended, Executor>
	{
	public:
		typedef Executor		    executor;
		typedef Executor::running   running;
		typedef Executor::suspended suspended;

		typedef void			 (*type)(suspended);

		basic_trigger() : __M_trigger_exec(nullptr) {  }
	public:
		void operator= (type      tr) {						  __M_trigger_exec = tr; }
		void operator()(suspended rq) { if (__M_trigger_exec) __M_trigger_exec(rq) ; }

	private:
		type __M_trigger_exec;
	};

	template <typename Executor>
	class basic_trigger<trigger::yielded, Executor>
	{
	public:
		typedef Executor		    executor;
		typedef Executor::running   running;
		typedef Executor::suspended suspended;

		typedef void			 (*type)(running);

		basic_trigger() : __M_trigger_exec(nullptr) {  }
	public:
		void operator= (type    tr) {						__M_trigger_exec = tr; }
		void operator()(running rq) { if (__M_trigger_exec) __M_trigger_exec(rq); }

	private:
		type __M_trigger_exec;
	};
}