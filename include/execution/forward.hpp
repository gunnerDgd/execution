#pragma once
#include <execution/basic_execution_branch.hpp>
#include <execution/trait_type.hpp>

#include <execution/execution_handle/basic_execution_handle.hpp>

namespace execution {
	typedef execution::basic_execution_handle<execution::execution_traits<context::context>>						   handle;
	typedef execution::basic_execution_branch<context::context, execution::execution_traits<context::context>, handle> branch;
}