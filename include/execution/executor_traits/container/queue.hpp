#include <type_traits>
#include <iterator>
#include <mutex>

#include <execution/execution_type.hpp>

namespace execution::queueing {
	template <typename BranchType>
	class queue
	{
	public:
		class   chain;
		class   iterator;
		typedef iterator		  queue_iterator;
		typedef queue<BranchType> queue_type;
		
		typedef std::mutex										queue_lock;
		typedef std::lock_guard<std::mutex>						queue_lock_guard;

		typedef std::remove_pointer_t<std::decay_t<BranchType>> value_type;
		typedef value_type&										reference_type;
		typedef value_type*										pointer_type;

	public:
		queue();

	public:
		iterator begin  ();
		iterator end    ();
		bool     empty  () { return (__M_queue_context_start == __M_queue_context_end); }

	public:
		template <typename EnqueueType>
		queue_iterator enqueue(EnqueueType&&, queue_iterator&, pointer_type) {  }
		template <typename EnqueueType>
		queue_iterator enqueue(EnqueueType&&, queue_iterator&, pointer_type) requires std::is_same_v<std::decay_t<EnqueueType>, execution_types::__avoid>;
		template <typename EnqueueType>
		queue_iterator enqueue(EnqueueType&&, queue_iterator&, pointer_type) requires std::is_same_v<std::decay_t<EnqueueType>, execution_types::__adjoint>;
		
		queue_iterator enqueue(pointer_type)		  ;

		void		   dequeue(iterator&)			  ;
		queue_iterator migrate(iterator&, queue_type&);

	private:
		chain	 * __M_queue_context,
				 * __M_queue_context_start, *__M_queue_context_end;
		queue_lock __M_queue_lock;
	};

	template <typename BranchType>
	class queue<BranchType>::chain
	{
		friend class queue<BranchType>;
		friend class queue<BranchType>::iterator;
	public:
		typedef queue<BranchType>		 queue_type;
		typedef queue<BranchType>::chain chain_type;

		using value_type			   = queue_type::value_type;
		using pointer				   = queue_type::pointer_type;
		using reference				   = queue_type::reference_type;

	public:
		chain(chain_type* prev, chain_type* next, pointer ptr) : __M_chain_prev  (prev),
																 __M_chain_next  (next),
																 __M_chain_branch(ptr) 
		{
			prev->__M_chain_next = this;
			next->__M_chain_prev = this;
		}
		chain () : __M_chain_branch(nullptr) {  }
		~chain()
		{
			__M_chain_prev->__M_chain_next = __M_chain_next;
			__M_chain_next->__M_chain_prev = __M_chain_prev;

			if(!__M_chain_branch)
				delete __M_chain_branch;
		}

		chain_type* __M_chain_prev, * __M_chain_next;
		pointer	    __M_chain_branch;
	};

	template <typename BranchType>
	class queue<BranchType>::iterator
	{
		friend class queue<BranchType>;
	public:
		typedef queue<BranchType>			queue_type;
		typedef queue<BranchType>::iterator iterator_type;
		typedef queue<BranchType>::chain	chain_type;
		
		using iterator_category = std::forward_iterator_tag;
		using difference_type   = std::ptrdiff_t;
		using value_type	    = queue_type::value_type;
		using pointer		    = queue_type::pointer_type;
		using reference		    = queue_type::reference_type;

	public:
		iterator(chain_type* ptr) : __M_it_chain(ptr)				{  }
		iterator(iterator&  copy) : __M_it_chain(copy.__M_it_chain) {  }
		iterator(iterator&& move) : __M_it_chain(move.__M_it_chain) { move.__M_it_chain = nullptr; }
		iterator()			      : __M_it_chain(nullptr)		    {  }

	public:
		iterator&      operator= (iterator_type&  copy) { __M_it_chain = copy.__M_it_chain;								  return *this; }
		iterator&      operator= (iterator_type&& move) { __M_it_chain = move.__M_it_chain; move.__M_it_chain = nullptr;  return *this; }

		bool		   operator==(iterator_type& cmp)  { return __M_it_chain == cmp.__M_it_chain; }
		bool		   operator!=(iterator_type& cmp)  { return __M_it_chain != cmp.__M_it_chain; }

		iterator_type& operator++() { __M_it_chain = __M_it_chain->__M_chain_next; return *this; }
		iterator_type& operator--() { __M_it_chain = __M_it_chain->__M_chain_prev; return *this; }
		reference	   operator* () 
		{
			if	    (__M_it_chain->__M_chain_branch == nullptr) ++(*this);
			return *(__M_it_chain->__M_chain_branch);
		}

	private:
		chain_type* __M_it_chain;
	};
}

template <typename BranchType>
execution::queueing::queue<BranchType>::queue() : __M_queue_context(new chain)
{
	__M_queue_context_start = __M_queue_context;
	__M_queue_context_end   = __M_queue_context;

	__M_queue_context->__M_chain_prev = __M_queue_context;
	__M_queue_context->__M_chain_next = __M_queue_context;
}

template <typename BranchType>
execution::queueing::queue<BranchType>::iterator execution::queueing::queue<BranchType>::begin()
{
	return iterator(__M_queue_context_start);
}

template <typename BranchType>
execution::queueing::queue<BranchType>::iterator execution::queueing::queue<BranchType>::end()
{
	return iterator(__M_queue_context_end);
}

template <typename BranchType>
execution::queueing::queue<BranchType>::queue_iterator execution::queueing::queue<BranchType>::enqueue(pointer_type ptr)
{
	queue_lock_guard enq_lock			  (__M_queue_lock);
	chain*			 enq_chain = new chain(__M_queue_context_end->__M_chain_prev, __M_queue_context_end, ptr);

	return iterator (enq_chain);
}

template <typename BranchType>
template <typename EnqueueType>
execution::queueing::queue<BranchType>::queue_iterator 
	execution::queueing::queue<BranchType>::enqueue(EnqueueType&&, queue_iterator& hnd, pointer_type ptr) requires std::is_same_v<std::decay_t<EnqueueType>, execution_types::__avoid>
{
	queue_lock_guard enq_lock			  (__M_queue_lock);
	chain*			 enq_chain = new chain(hnd.__M_it_chain->__M_chain_prev, hnd.__M_it_chain, ptr);

	return iterator (enq_chain);
}

template <typename BranchType>
template <typename EnqueueType>
execution::queueing::queue<BranchType>::queue_iterator 
	execution::queueing::queue<BranchType>::enqueue(EnqueueType&&, queue_iterator& hnd, pointer_type ptr) requires std::is_same_v<std::decay_t<EnqueueType>, execution_types::__adjoint>
{
	queue_lock_guard enq_lock			  (__M_queue_lock);
	chain*			 enq_chain = new chain(hnd.__M_it_chain, hnd.__M_it_chain->__M_chain_next, ptr);

	return iterator (enq_chain);
}

template <typename BranchType>
void execution::queueing::queue<BranchType>::dequeue(iterator& it)
{
	queue_lock_guard deq_lock(__M_queue_lock);
	delete				   it.__M_it_chain.__M_chain_branch;
						   it = iterator  (__M_queue_context_start);
}

template <typename BranchType>
execution::queueing::queue<BranchType>::queue_iterator execution::queueing::queue<BranchType>::migrate(iterator& it, queue_type& q)
{
	queue_lock_guard mig_lock(__M_queue_lock);
	pointer_type	 br_mig = &(*it);
							     it.__M_it_chain->__M_chain_branch = nullptr;
	
	delete it.__M_it_chain;
		   it = iterator(__M_queue_context_start);

	return q.enqueue(br_mig);
}