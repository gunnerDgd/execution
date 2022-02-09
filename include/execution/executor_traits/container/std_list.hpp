#pragma once
#include <list>

#include <execution/executor_traits/container/ringed_list.hpp>
#include <execution/forward.hpp>

namespace execution::queueing {
	template <typename BranchType>
	class std_list
	{
	public:
		typedef std::remove_pointer_t<std::decay_t<BranchType>> branch_type;
		typedef branch_type*									branch_pointer;
		typedef branch_type&									branch_reference;

		typedef			 std::list<branch_pointer>				queue_type;
		typedef typename std::list<branch_pointer>::iterator	queue_iterator;

	public:
		queue_iterator enqueue   (branch_pointer);
		queue_iterator enqueue_at(branch_pointer, queue_iterator&);
		
		void		   dequeue   (queue_iterator&);
		queue_iterator migrate   (queue_iterator&, queue_type&);
		queue_iterator 

	private:
		queue_type __M_stdlist_queue; // Running
	};
}		using namespace execution::queueing;

template <typename BranchType>
std_list<BranchType>::queue_iterator std_list<BranchType>::enqueue   (branch_pointer enq)
{
	__M_stdlist_queue.push_back(enq);
}

template <typename BranchType>
std_list<BranchType>::queue_iterator std_list<BranchType>::enqueue_at(branch_pointer enq, queue_iterator& enq_pos)
{
	__M_stdlist_queue.insert(enq_pos, enq);
	return				  		    ++enq ;
}

template <typename BranchType>
void								 std_list<BranchType>::dequeue(queue_iterator& deq)
{
	__M_stdlist_queue.erase(deq);
}

template <typename BranchType>
std_list<BranchType>::queue_iterator std_list<BranchType>::migrate(queue_iterator& mig, queue_type& mig_queue)
{
	branch_pointer mig_branch = *mig;
	
	__M_stdlist_queue.erase	    (mig);
	mig_queue.push_back			(mig_branch);

	return --(mig_queue.end());
}