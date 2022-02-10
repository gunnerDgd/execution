#pragma once
#include <execution/trigger/category.hpp>
#include <functional>

namespace execution {
	template <typename Category, typename Executor>
	class basic_trigger;

	template <typename Executor>
	class basic_trigger<trigger::executed, Executor>
	{
	public:
		typedef Executor					 executor;
		typedef Executor::running			 running;
		typedef Executor::suspended			 suspended;
		typedef std::function<void(running)> type;

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
		typedef Executor					 executor;
		typedef Executor::running			 running;
		typedef Executor::suspended			 suspended;
		typedef std::function<void(running)> type;

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
		typedef Executor					   executor;
		typedef Executor::running			   running;
		typedef Executor::suspended			   suspended;
		typedef std::function<void(suspended)> type;

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
		typedef Executor					 executor;
		typedef Executor::running			 running;
		typedef Executor::suspended			 suspended;
		typedef std::function<void(running)> type;

	public:
		template <typename Action>
		void operator= (Action&& tr) {						 __M_trigger_exec = tr ; }
		void operator()(running rq)  { if (__M_trigger_exec) __M_trigger_exec  (rq); }

	private:
		type __M_trigger_exec;
	};
}