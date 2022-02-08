#pragma once
#include <context/forward.hpp>
#include <context/stack/forward.hpp>

#include <execution/trait_type.hpp>

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
		static auto  to_pack(context::context&, context::context&, ExecType&&, ExecHandle&&, ExecArgs&&...);

	public:
		template <typename... PackType>
		static void execute_at(execution_pack<PackType...>*);
		static void switch_to (context::context&, context::context&);
	};

	template <typename ExecType, typename ExecHandle, typename... ExecArgs>
	class execution_traits<context::context>::execution_pack
	{
	public:
		typedef ExecType				execution_type;
		typedef std::tuple<ExecArgs...> argument_type ;
		typedef ExecHandle				handle_type   ;

		execution_pack(context::context&, context::context&, handle_type&, execution_type, argument_type&&);

		handle_type&					__M_pack_handle;
		execution_type				    __M_pack_exec;
		argument_type					__M_pack_args;

		context::context&				__M_pack_prev, 
						&				__M_pack_curr;
	};

	template <typename ExecType, typename ExecHandle>
	class execution_traits<context::context>::execution_pack<ExecType, ExecHandle>
	{
	public:
		typedef ExecType				execution_type;
		typedef ExecHandle				handle_type;

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
auto execution::execution_traits<context::context>::to_pack(context::context& prev, context::context& curr, ExecType&& exec, ExecHandle&& hnd, ExecArgs&&... args)
{
	return new execution_pack<ExecType, ExecArgs...>(prev, curr, exec, hnd, std::make_tuple(args...));
}

template <typename... PackType>
void execution::execution_traits<context::context>::execute_at(execution_pack<PackType...>* pack)
{
	context::context::execute_at(pack->__M_pack_prev, pack->__M_pack_curr, [](void* pack_ptr) 
		{
			execution_pack<PackType...>*							  pack = reinterpret_cast<execution_pack<PackType...>*>(pack_ptr);
			{
				typename execution_pack<PackType...>::handle_type::status pack_status(pack->__M_pack_handle);

				context::context::switch_to (pack->__M_pack_curr, pack->__M_pack_prev);
				std::apply				    (pack->__M_pack_exec, std::tuple_cat(std::tuple<typename execution_pack<PackType...>::handle_type&>(pack->__M_pack_handle), pack->__M_pack_args));
			}
			delete pack;
		}, (void*)pack);
}

void execution::execution_traits<context::context>::switch_to(context::context& prev, context::context& curr)
{
	context::context::switch_to(prev, curr);
}