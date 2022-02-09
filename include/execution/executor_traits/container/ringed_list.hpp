#pragma once
#include <memory>
#include <type_traits>

namespace execution::queueing {
	template <typename BlockType, typename BlockAllocator = std::allocator<BlockType>>
	class ringed_list
	{
		class									       rlist_wrapper  ;
	public:
		class									       rlist_iterator ;
		typedef rlist_iterator					       iterator_type  ;
		typedef BlockAllocator					       allocator_type ;
		
		typedef std::remove_reference_t<BlockType>	   block_type	  ;
		typedef block_type&							   block_reference;
		typedef block_type*							   block_pointer  ;

		typedef ringed_list<BlockType, BlockAllocator> this_type;

		ringed_list ();
		~ringed_list();
	public:
		iterator_type begin();
		iterator_type end  ();

	public:
		template <typename InputType>
		iterator_type enqueue   (InputType&&)				 requires std::is_same_v<std::decay_t<InputType>, block_type>;
		template <typename InputType>
		iterator_type enqueue_at(InputType&&, iterator_type&) requires std::is_same_v<std::decay_t<InputType>, block_type>;
		void		  dequeue	(iterator_type&);
		iterator_type migrate   (iterator_type&, this_type&);
		
	private:
		allocator_type __M_rlist_allocator;
		rlist_wrapper* __M_rlist_begin = nullptr, 
					 * __M_rlist_end   = nullptr;
	};

	template <typename BlockType, typename BlockAllocator>
	class ringed_list<BlockType, BlockAllocator>::rlist_iterator
	{
		friend class	 ringed_list<BlockType, BlockAllocator>;
		typedef typename ringed_list<BlockType, BlockAllocator>::rlist_wrapper wrapper_type;
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type   = std::ptrdiff_t;
		using value_type		= typename ringed_list<BlockType, BlockAllocator>::block_type	  ;
		using pointer			= typename ringed_list<BlockType, BlockAllocator>::block_pointer  ;
		using reference		    = typename ringed_list<BlockType, BlockAllocator>::block_reference;

	public:
		reference		operator* ();
		rlist_iterator& operator++();
		bool			operator==(rlist_iterator&);
		bool			operator!=(rlist_iterator&);

	private:
		wrapper_type* __M_iterator_wrapper;
	};

	template <typename BlockType, typename BlockAllocator>
	class ringed_list<BlockType, BlockAllocator>::rlist_wrapper
	{
		friend class ringed_list<BlockType, BlockAllocator>;
		friend class ringed_list<BlockType, BlockAllocator>::rlist_iterator;
	public:
		typedef ringed_list<BlockType, BlockAllocator> rlist_type;
		
		typedef typename rlist_type::block_type        block_type	  ;
		typedef block_type*							   block_pointer  ;
		typedef block_type&							   block_reference;
	
		typedef typename rlist_type::rlist_wrapper	   this_type;
		typedef this_type*							   this_pointer  ;
		typedef this_type&							   this_reference;

	private:
		this_pointer  __M_wrapper_prev   ;
		this_pointer  __M_wrapper_next   ;
		block_pointer __M_wrapper_context;
	};
}

using namespace execution::queueing;

template <typename BlockType, typename BlockAllocator>
ringed_list<BlockType, BlockAllocator>::ringed_list ()
{
	
}

template <typename BlockType, typename BlockAllocator>
ringed_list<BlockType, BlockAllocator>::~ringed_list()
{

}

template <typename BlockType, typename BlockAllocator>
ringed_list<BlockType, BlockAllocator>::rlist_iterator::reference ringed_list<BlockType, BlockAllocator>::rlist_iterator::operator* ()
{
	return *__M_iterator_wrapper->__M_wrapper_context;
}

template <typename BlockType, typename BlockAllocator>
ringed_list<BlockType, BlockAllocator>::rlist_iterator& ringed_list<BlockType, BlockAllocator>::rlist_iterator::operator++()
{
	__M_iterator_wrapper = __M_iterator_wrapper->__M_wrapper_next;
	return *this;
}

template <typename BlockType, typename BlockAllocator>
bool			ringed_list<BlockType, BlockAllocator>::rlist_iterator::operator==(rlist_iterator& rv)
{
	return (__M_iterator_wrapper == rv.__M_iterator_wrapper);
}

template <typename BlockType, typename BlockAllocator>
bool			ringed_list<BlockType, BlockAllocator>::rlist_iterator::operator!=(rlist_iterator& rv)
{
	return (__M_iterator_wrapper != rv.__M_iterator_wrapper);
}

template <typename BlockType, typename BlockAllocator>
template <typename InputType>
ringed_list<BlockType, BlockAllocator>::iterator_type ringed_list<BlockType, BlockAllocator>::enqueue   (InputType&& input)					   requires std::is_same_v<std::decay_t<InputType>, block_type>
{
	rlist_wrapper* input_wrapper       = new rlist_wrapper;
	input_wrapper->__M_wrapper_context = __M_rlist_allocator.allocate(1); std::construct_at(input_wrapper->__M_wrapper_context, input);
	
	input_wrapper->__M_wrapper_prev	   = __M_rlist_end;
	input_wrapper->__M_wrapper_next	   = __M_rlist_begin;

	__M_rlist_end  ->__M_wrapper_next  = input_wrapper;
	__M_rlist_begin->__M_wrapper_prev  = input_wrapper;

	iterator_type input_iterator;
				  input_iterator.__M_iterator_wrapper = input_wrapper;

	return		  input_iterator;
}

template <typename BlockType, typename BlockAllocator>
void ringed_list<BlockType, BlockAllocator>::dequeue(iterator_type& pos)
{
	pos.__M_iterator_wrapper->__M_wrapper_prev->__M_wrapper_next = pos.__M_iterator_wrapper->__M_wrapper_next;
	pos.__M_iterator_wrapper->__M_wrapper_next->__M_wrapper_prev = pos.__M_iterator_wrapper->__M_wrapper_prev;

	delete pos.__M_iterator_wrapper->__M_wrapper_context;
	delete pos.__M_iterator_wrapper;
}

template <typename BlockType, typename BlockAllocator>
ringed_list<BlockType, BlockAllocator>::iterator_type ringed_list<BlockType, BlockAllocator>::migrate(iterator_type& hnd, this_type& queue)
{
	hnd.__M_iterator_wrapper->__M_wrapper_prev->__M_wrapper_next = hnd.__M_iterator_wrapper->__M_wrapper_next;
	hnd.__M_iterator_wrapper->__M_wrapper_next->__M_wrapper_prev = hnd.__M_iterator_wrapper->__M_wrapper_prev;

	return queue.enqueue(*hnd.__M_iterator_wrapper->__M_wrapper_context);
}

template <typename BlockType, typename BlockAllocator>
template <typename InputType>
ringed_list<BlockType, BlockAllocator>::iterator_type ringed_list<BlockType, BlockAllocator>::enqueue_at(InputType&& input, iterator_type& pos) requires std::is_same_v<std::decay_t<InputType>, block_type>
{
	rlist_wrapper* input_wrapper       = new rlist_wrapper;
	input_wrapper->__M_wrapper_context = __M_rlist_allocator.allocate(1); std::construct_at(input_wrapper->__M_wrapper_context, input);

	input_wrapper->__M_wrapper_prev	   = pos.__M_iterator_wrapper;
	input_wrapper->__M_wrapper_next    = pos.__M_iterator_wrapper->__M_wrapper_next;

	pos.__M_iterator_wrapper->__M_wrapper_next->__M_wrapper_prev = input_wrapper;
	pos.__M_iterator_wrapper->__M_wrapper_next					 = input_wrapper;
}

template <typename BlockType, typename BlockAllocator>
ringed_list<BlockType, BlockAllocator>::iterator_type ringed_list<BlockType, BlockAllocator>::begin()
{
	rlist_iterator b_iterator;
				   b_iterator.__M_iterator_wrapper = __M_rlist_begin; 

	return		   b_iterator;
}

template <typename BlockType, typename BlockAllocator>
ringed_list<BlockType, BlockAllocator>::iterator_type ringed_list<BlockType, BlockAllocator>::end  ()
{
	rlist_iterator e_iterator;
				   e_iterator.__M_iterator_wrapper = __M_rlist_end; 

	return		   e_iterator;
}