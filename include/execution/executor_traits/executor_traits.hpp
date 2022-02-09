#pragma once
#include <execution/executor_traits/container/ringed_list.hpp>
#include <execution/forward.hpp>

#include <mutex>

#define EXECUTION_LOCK_QUEUE(lock, name) std::lock_guard<std::mutex> name(lock);

namespace execution {
	template <typename ExecutorBranch>
	class executor_traits;

	template <>
	class executor_traits<branch>
	{
		class								  execution_handle;
		class								  suspended_handle;
	public:
		typedef branch						  branch_type;
		typedef branch*						  branch_pointer;
		typedef branch&						  branch_reference;

		typedef std::mutex					  lock_type  ;
		typedef branch::branch_handle::status state_type ;

	public:
		typedef execution_handle			  running_branch  ;
		typedef suspended_handle			  suspended_branch;

	public:
		template <typename ExecType, typename... ExecArgs>
		running_branch   start  (ExecType&&, ExecArgs&&...);
		running_branch   start  (suspended_branch&);

		void			 end    (running_branch  &);
		void			 end    (suspended_branch&);

		suspended_handle suspend(running_branch  &);

	private:
		queueing::ringed_list<branch_pointer>::iterator_type __M_traits_iterator  ;
		queueing::ringed_list<branch_pointer>				 __M_traits_queue     ;
		lock_type										     __M_traits_queue_lock;

	private:
		queueing::ringed_list<branch_pointer>::iterator_type __M_traits_suspend_iterator;
		queueing::ringed_list<branch_pointer>				 __M_traits_suspend_queue;
		lock_type										     __M_traits_suspend_queue_lock;
	};

	class executor_traits<branch>::execution_handle
	{
		template <typename T, typename U>
		friend class basic_executor;
		friend class executor_traits<branch>;

		execution_handle (queueing::ringed_list<branch_pointer>::iterator_type br) : __M_handle_branch(br){  }

	public:
		branch::branch_handle::status state() { (**__M_handle_branch).state(); }

	private:
		queueing::ringed_list<branch_pointer>::iterator_type __M_handle_branch;
	};

	class executor_traits<branch>::suspended_handle
	{
		template <typename T, typename U>
		friend class basic_executor;
		friend class executor_traits<branch>;

		suspended_handle(queueing::ringed_list<branch_pointer>::iterator_type br) : __M_handle_branch(br) {  }

	public:
		branch::branch_handle::status state() { (**__M_handle_branch).state(); }

	private:
		queueing::ringed_list<branch_pointer>::iterator_type __M_handle_branch;
	};

}

execution::executor_traits<execution::branch>::running_branch execution::executor_traits<execution::branch>::start(suspended_branch& suspended)
{
	EXECUTION_LOCK_QUEUE (__M_traits_queue_lock		   , rq_lock)
	EXECUTION_LOCK_QUEUE (__M_traits_suspend_queue_lock, sq_lock)

	return running_branch(__M_traits_suspend_queue.migrate(suspended.__M_handle_branch, __M_traits_queue));
}

template <typename ExecType, typename... ExecArgs>
execution::executor_traits<execution::branch>::running_branch execution::executor_traits<execution::branch>::start(ExecType&& exec, ExecArgs&&... args)
{
	EXECUTION_LOCK_QUEUE (__M_traits_queue_lock, rq_lock)
	return running_branch(__M_traits_queue.enqueue(new branch(exec, std::forward<ExecArgs>(args)...)));
}

void execution::executor_traits<execution::branch>::end(running_branch& hnd)
{
	EXECUTION_LOCK_QUEUE	(__M_traits_queue_lock, rq_lock)
	__M_traits_queue.dequeue(hnd.__M_handle_branch);
}

void execution::executor_traits<execution::branch>::end(suspended_branch& hnd)
{
	EXECUTION_LOCK_QUEUE			(__M_traits_suspend_queue_lock, sq_lock)
	__M_traits_suspend_queue.dequeue(hnd.__M_handle_branch);
}

execution::executor_traits<execution::branch>::suspended_handle execution::executor_traits<execution::branch>::suspend(running_branch& running)
{
	EXECUTION_LOCK_QUEUE   (__M_traits_queue_lock		 , rq_lock)
	EXECUTION_LOCK_QUEUE   (__M_traits_suspend_queue_lock, sq_lock)

	return suspended_handle(__M_traits_queue.migrate(running.__M_handle_branch, __M_traits_suspend_queue));
}