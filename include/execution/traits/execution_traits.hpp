#pragma once
#include <context/forward.hpp>
#include <context/stack/forward.hpp>

#include <execution/trait_type.hpp>
#include <execution/execution_status.hpp>

#include <iostream>

#include <type_traits>
#include <tuple>

namespace execution {
	template <>
	class execution_traits<context::context>
	{
	public:
		typedef context::context context_type;

		template <typename ExecType, typename... ExecArgs>
		class execution_pack;
		
		template <typename ExecType, typename... ExecArgs>
		static auto to_pack(context::context&, context::context&, execution_state&, ExecType&&, ExecArgs&&...) requires (sizeof...(ExecArgs) > 0);	

		template <typename ExecType>
		static auto to_pack(context::context&, context::context&, execution_state&, ExecType&&);

	public:
		template <typename ExecHandle, typename... PackType>
		static void execute_at(execution_pack<PackType...>*);
		template <typename ExecHandle, typename... PackType>
		static void execute_at(execution_pack<PackType...>*) requires (sizeof...(PackType) == 1);
		static void switch_to (context::context&, context::context&);
	};

	template <typename ExecType, typename... ExecArgs>
	class execution_traits<context::context>::execution_pack
	{
	public:
		typedef ExecType  			    execution_type;
		typedef std::tuple<ExecArgs...> argument_type ;

		execution_pack(context::context&, context::context&, execution_state&, execution_type, argument_type&&);

		execution_type	  __M_pack_exec;
		execution_state&  __M_pack_exec_state;
		argument_type	  __M_pack_args;

		context::context& __M_pack_prev, 
						& __M_pack_curr;
	};

	template <typename ExecType>
	class execution_traits<context::context>::execution_pack<ExecType>
	{
	public:
		typedef ExecType execution_type;

		execution_pack(context::context&, context::context&, execution_state&, execution_type);

		execution_type	  __M_pack_exec;
		execution_state&  __M_pack_exec_state;

		context::context& __M_pack_prev,
						& __M_pack_curr;
	};
}

template <typename ExecType, typename... ExecArgs>
execution::execution_traits<context::context>::execution_pack<ExecType, ExecArgs...>::execution_pack(context::context& prev, context::context& curr, execution_state& state, execution_type exec, argument_type&& args)
	: __M_pack_prev		 (prev),
	  __M_pack_curr		 (curr),
	  __M_pack_args	     (std::move(args)),
	  __M_pack_exec		 (exec),
	  __M_pack_exec_state(state)		  {  }

template <typename ExecType>
execution::execution_traits<context::context>::execution_pack<ExecType>::execution_pack(context::context& prev, context::context& curr, execution_state& state, execution_type exec)
	: __M_pack_prev		 (prev),
	  __M_pack_curr		 (curr),
	  __M_pack_exec		 (exec),
	  __M_pack_exec_state(state) {  }

template <typename ExecType, typename... ExecArgs>
auto execution::execution_traits<context::context>::to_pack(context::context& prev, context::context& curr, execution_state& state, ExecType&& exec, ExecArgs&&... args) requires (sizeof...(ExecArgs) > 0)
{
	return new execution_pack<ExecType, ExecArgs...>(prev, curr, state, exec, std::tuple<ExecArgs...>(args...));
}

template <typename ExecType>
auto execution::execution_traits<context::context>::to_pack(context::context& prev, context::context& curr, execution_state& state, ExecType&& exec)
{
	return new execution_pack<ExecType>(prev, curr, state, exec);
}

template <typename ExecHandle, typename... PackType>
void execution::execution_traits<context::context>::execute_at(execution_pack<PackType...>* pack)
{
	context::context::execute_at(pack->__M_pack_prev, pack->__M_pack_curr, [](void* pack_ptr) 
	{
		execution_pack<PackType...>* pack = reinterpret_cast<execution_pack<PackType...>*>(pack_ptr);
		context::context::switch_to (pack->__M_pack_curr, pack->__M_pack_prev);

		ExecHandle*					 pack_handle = new ExecHandle(pack->__M_pack_prev, pack->__M_pack_curr, pack->__M_pack_exec_state);
		std::apply				    (pack->__M_pack_exec, std::tuple_cat(std::tuple<ExecHandle&>(*pack_handle), pack->__M_pack_args));
		
		context::context& parent   = pack->__M_pack_prev, & current = pack->__M_pack_curr;
		delete						 pack;
		delete						 pack_handle;
		
		context::context::switch_to (current, parent);
		
	}, (void*)pack);
}

template <typename ExecHandle, typename... PackType>
void execution::execution_traits<context::context>::execute_at(execution_pack<PackType...>* pack) requires (sizeof...(PackType) == 1)
{
	context::context::execute_at(pack->__M_pack_prev, pack->__M_pack_curr, [](void* pack_ptr) 
	{
		execution_pack<PackType...>* pack = reinterpret_cast<execution_pack<PackType...>*>(pack_ptr);
		context::context::switch_to (pack->__M_pack_curr, pack->__M_pack_prev);

		ExecHandle*					 pack_handle = new ExecHandle(pack->__M_pack_prev, pack->__M_pack_curr, pack->__M_pack_exec_state);
		std::apply				    (pack->__M_pack_exec, std::tuple<ExecHandle&>(*pack_handle));
			
		context::context& parent   = pack->__M_pack_prev, & current = pack->__M_pack_curr;
		delete					     pack;
		delete						 pack_handle;
			
		context::context::switch_to (current, parent);
	}, (void*)pack);
}

void execution::execution_traits<context::context>::switch_to(context::context& prev, context::context& curr)
{
	context::context::switch_to(prev, curr);
}