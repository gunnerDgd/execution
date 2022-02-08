#pragma once
#include <context/forward.hpp>
#include <context/stack/forward.hpp>

#include <execution/trait_type.hpp>

#include <iostream>

#include <type_traits>
#include <tuple>

namespace execution {

	template <>
	class execution_traits<context::context>
	{
	public:
		typedef context::context context_type;

		template <typename ExecType, typename ExecHandle, typename... ExecArgs >
		class execution_pack  ;
		
		template <typename ExecType, typename ExecHandle, typename... ExecArgs>
		static auto  to_pack(context::context&, context::context&, ExecType&&, ExecHandle&&, ExecArgs&&...) requires (sizeof...(ExecArgs) > 0);	

		template <typename ExecType, typename ExecHandle>
		static auto  to_pack(context::context&, context::context&, ExecType&&, ExecHandle&&);

	public:
		template <typename... PackType>
		static void execute_at(execution_pack<PackType...>*);
		template <typename... PackType>
		static void execute_at(execution_pack<PackType...>*) requires (sizeof...(PackType) == 2);

		static void switch_to (context::context&, context::context&);
	};

	template <typename ExecType, typename ExecHandle, typename... ExecArgs>
	class execution_traits<context::context>::execution_pack
	{
	public:
		typedef ExecType				  execution_type;
		typedef std::tuple  <ExecArgs...> argument_type ;
		typedef std::decay_t<ExecHandle>  handle_type   ;

		execution_pack(context::context&, context::context&, handle_type&, execution_type, argument_type&&);

		handle_type&	  __M_pack_handle;
		execution_type	  __M_pack_exec;
		argument_type	  __M_pack_args;

		context::context& __M_pack_prev, 
						& __M_pack_curr;
	};

	template <typename ExecType, typename ExecHandle>
	class execution_traits<context::context>::execution_pack<ExecType, ExecHandle>
	{
	public:
		typedef						ExecType		    execution_type;
		typedef	std::remove_cvref_t<ExecHandle>		    handle_type;
		typedef typename		    handle_type::status handle_status;

		execution_pack(context::context&, context::context&, handle_type&, execution_type);

		handle_type&      __M_pack_handle;
		execution_type	  __M_pack_exec;

		context::context& __M_pack_prev,
						& __M_pack_curr;
	};
}

template <typename ExecType, typename ExecHandle, typename... ExecArgs>
execution::execution_traits<context::context>::execution_pack<ExecType, ExecHandle, ExecArgs...>::execution_pack(context::context& prev, context::context& curr, handle_type& hnd, execution_type exec, argument_type&& args)
	: __M_pack_handle(hnd),
	  __M_pack_prev  (prev),
	  __M_pack_curr  (curr),
	  __M_pack_exec  (exec),
	  __M_pack_args  (std::move(args)) {  }

template <typename ExecType, typename ExecHandle>
execution::execution_traits<context::context>::execution_pack<ExecType, ExecHandle>::execution_pack(context::context& prev, context::context& curr, handle_type& hnd, execution_type exec)
	: __M_pack_handle(hnd),
	  __M_pack_prev  (prev),
	  __M_pack_curr  (curr),
	  __M_pack_exec  (exec) {  }

template <typename ExecType, typename ExecHandle, typename... ExecArgs>
auto execution::execution_traits<context::context>::to_pack(context::context& prev, context::context& curr, ExecType&& exec, ExecHandle&& hnd, ExecArgs&&... args) requires (sizeof...(ExecArgs) > 0)
{
	return new execution_pack<ExecType, ExecHandle, ExecArgs...>(prev, curr, hnd, exec, std::tuple<ExecArgs...>(args...));
}

template <typename ExecType, typename ExecHandle>
auto execution::execution_traits<context::context>::to_pack(context::context& prev, context::context& curr, ExecType&& exec, ExecHandle&& hnd)
{
	return new execution_pack<ExecType, ExecHandle>(prev, curr, hnd, exec);
}

template <typename... PackType>
void execution::execution_traits<context::context>::execute_at(execution_pack<PackType...>* pack)
{
	context::context::execute_at(pack->__M_pack_prev, pack->__M_pack_curr, [](void* pack_ptr) 
		{
			execution_pack<PackType...>* pack = reinterpret_cast<execution_pack<PackType...>*>(pack_ptr);
			{
				typename execution_pack<PackType...>::handle_type::status pack_status(pack->__M_pack_handle);

				context::context::switch_to (pack->__M_pack_curr, pack->__M_pack_prev);
				std::apply				    (pack->__M_pack_exec, std::tuple_cat(std::tuple<typename execution_pack<PackType...>::handle_type&>(pack->__M_pack_handle), pack->__M_pack_args));
			}
				context::context::switch_to (pack->__M_pack_curr, pack->__M_pack_prev);
		}, (void*)pack);
}

template <typename... PackType>
void execution::execution_traits<context::context>::execute_at(execution_pack<PackType...>* pack) requires (sizeof...(PackType) == 2)
{
	context::context::execute_at(pack->__M_pack_prev, pack->__M_pack_curr, [](void* pack_ptr) 
		{
			execution_pack<PackType...>*							      pack = reinterpret_cast<execution_pack<PackType...>*>(pack_ptr);
			{
				typename execution_pack<PackType...>::handle_type::status pack_status(pack->__M_pack_handle);

				context::context::switch_to (pack->__M_pack_curr, pack->__M_pack_prev);
				std::apply				    (pack->__M_pack_exec, std::tuple<typename execution_pack<PackType...>::handle_type&>(pack->__M_pack_handle));
			}
			context::context& parent = pack->__M_pack_prev, & current = pack->__M_pack_curr;
			delete					   pack;

			context::context::switch_to(current, parent);
		}, (void*)pack);
}

void execution::execution_traits<context::context>::switch_to(context::context& prev, context::context& curr)
{
	context::context::switch_to(prev, curr);
}