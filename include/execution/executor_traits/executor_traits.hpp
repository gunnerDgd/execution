#pragma once
#include <execution/executor_traits/container/ringed_list.hpp>
#include <execution/forward.hpp>

#include <mutex>

#define EXECUTION_LOCK_QUEUE(lock, name) std::lock_guard<std::mutex> name(lock);

namespace execution {
	template <typename ExecutorBranch, typename ExecutorQueue>
	class executor_traits;

	template <typename ExecutorQueue>
	class executor_traits<branch, ExecutorQueue>
	{
	public:
		typedef branch						  branch_type	  ;
		typedef branch*						  branch_pointer  ;
		typedef branch&						  branch_reference;

		typedef std::mutex					  lock_type  ;
		typedef branch::branch_handle::status state_type ;

		class running;
		class suspended;

	private:
		typedef			 ExecutorQueue			 queue_type;
		typedef typename ExecutorQueue::iterator queue_iterator;

	public:
		template <typename ExecType, typename... ExecArgs>
		running   start  (ExecType&&, ExecArgs&&...);
		running   start  (suspended&);

		void	  end    (running&);
		void	  end    (suspended&);

		suspended suspend(running&);

		branch_reference current()				   { return (__M_traits_iterator) ? **__M_traits_iterator     : **(__M_traits_iterator = __M_traits_queue.begin()); }
		branch_reference next   ()				   { return (__M_traits_iterator) ? **(++__M_traits_iterator) : **(__M_traits_iterator = __M_traits_queue.begin()); }
	private:
		queue_iterator __M_traits_iterator  ;
		queue_type	   __M_traits_queue     ;
		lock_type	   __M_traits_queue_lock;

	private:
		queue_type     __M_traits_suspend_queue;
		lock_type	   __M_traits_suspend_queue_lock;
	};

	template <typename ExecutorQueue>
	class executor_traits<branch, ExecutorQueue>::running
	{
		template <typename T, typename U>
		friend class basic_executor;
		template <typename T>
		friend class executor_traits<branch, T>;

		using queue_type     = typename executor_traits<branch, ExecutorQueue>::queue_type	  ;
		using queue_iterator = typename executor_traits<branch, ExecutorQueue>::queue_iterator;
		using status		 = typename branch::branch_handle::status;

		running(queue_iterator br) : __M_handle_branch(br){  }

	public:
		status state() { return (**__M_handle_branch).state(); }

	private:
		queue_iterator __M_handle_branch;
	};

	template <typename ExecutorQueue>
	class executor_traits<branch, ExecutorQueue>::suspended
	{
		template <typename T, typename U>
		friend class basic_executor;
		template <typename T>
		friend class executor_traits<branch, T>;

		using queue_type     = typename executor_traits<branch, ExecutorQueue>::queue_type	  ;
		using queue_iterator = typename executor_traits<branch, ExecutorQueue>::queue_iterator;
		using status		 = typename branch::branch_handle::status;

		suspended(queue_iterator br) : __M_handle_branch(br) {  }

	public:
		status state() { (**__M_handle_branch).state(); }

	private:
		queue_iterator __M_handle_branch;
	};

}

template <typename ExecutorQueue>
execution::executor_traits<execution::branch, ExecutorQueue>::running execution::executor_traits<execution::branch, ExecutorQueue>::start(suspended& suspended)
{
	if (!suspended.__M_handle_branch) return running_branch { queue_iterator{} };

	EXECUTION_LOCK_QUEUE (__M_traits_queue_lock		   , rq_lock)
	EXECUTION_LOCK_QUEUE (__M_traits_suspend_queue_lock, sq_lock)

	queue_iterator s_it = suspended.__M_handle_branch;
						  suspended.__M_handle_branch = queue_iterator();
	
	return running_branch(__M_traits_suspend_queue.migrate(s_it, __M_traits_queue));
}

template <typename ExecutorQueue>
template <typename ExecType, typename... ExecArgs>
execution::executor_traits<execution::branch, ExecutorQueue>::running execution::executor_traits<execution::branch, ExecutorQueue>::start(ExecType&& exec, ExecArgs&&... args)
{
	EXECUTION_LOCK_QUEUE (__M_traits_queue_lock, rq_lock)
	return running_branch(__M_traits_queue.enqueue(new branch(exec, std::forward<ExecArgs>(args)...)));
}

template <typename ExecutorQueue>
void execution::executor_traits<execution::branch, ExecutorQueue>::end(running& hnd)
{
	EXECUTION_LOCK_QUEUE(__M_traits_queue_lock, rq_lock)
						 __M_traits_queue.dequeue(hnd.__M_handle_branch);
}

template <typename ExecutorQueue>
void execution::executor_traits<execution::branch, ExecutorQueue>::end(suspended& hnd)
{
	EXECUTION_LOCK_QUEUE(__M_traits_suspend_queue_lock, sq_lock)
						 __M_traits_suspend_queue.dequeue(hnd.__M_handle_branch);
}

template <typename ExecutorQueue>
execution::executor_traits<execution::branch, ExecutorQueue>::suspended execution::executor_traits<execution::branch, ExecutorQueue>::suspend(running& running)
{
	if (!running.__M_handle_branch) return suspended_branch{ queue_iterator{} };

	EXECUTION_LOCK_QUEUE   (__M_traits_queue_lock		 , rq_lock)
	EXECUTION_LOCK_QUEUE   (__M_traits_suspend_queue_lock, sq_lock)
	
	queue_iterator r_it = running.__M_handle_branch;
					      running.__M_handle_branch = queue_iterator();
						  
	return suspended_handle(__M_traits_queue.migrate(r_it, __M_traits_suspend_queue));
}