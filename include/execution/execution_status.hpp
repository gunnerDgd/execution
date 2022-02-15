#pragma once
#include <cstdint>
#include <cstddef>

#include <type_traits>

namespace execution {
	enum class execution_state : std::uint8_t
	{ 
		standby   = 1, 
		running   = 1 << 1, 
		yielded   = 1 << 2, 
		suspended = 1 << 3, 
		ended	  = 1 << 4
	};

	std::underlying_type_t<execution_state> operator| (execution_state, execution_state);
	std::underlying_type_t<execution_state> operator^ (execution_state, execution_state);
	std::underlying_type_t<execution_state> operator& (execution_state, execution_state);

	std::underlying_type_t<execution_state> operator|= (execution_state, execution_state);
	std::underlying_type_t<execution_state> operator^= (execution_state, execution_state);
	std::underlying_type_t<execution_state> operator&= (execution_state, execution_state);
}

std::underlying_type_t<execution::execution_state> execution::operator| (execution_state lhs, execution_state rhs)
{
	return std::underlying_type_t<execution::execution_state>(lhs) | std::underlying_type_t<execution_state>(rhs);
}

std::underlying_type_t<execution::execution_state> execution::operator^ (execution_state lhs, execution_state rhs)
{
	return std::underlying_type_t<execution::execution_state>(lhs) ^ std::underlying_type_t<execution_state>(rhs);
}

std::underlying_type_t<execution::execution_state> execution::operator& (execution_state lhs, execution_state rhs)
{
	return std::underlying_type_t<execution::execution_state>(lhs) & std::underlying_type_t<execution_state>(rhs);
}

std::underlying_type_t<execution::execution_state> execution::operator|= (execution_state lhs, execution_state rhs)
{
	return std::underlying_type_t<execution::execution_state>(lhs) | std::underlying_type_t<execution_state>(rhs);
}

std::underlying_type_t<execution::execution_state> execution::operator^= (execution_state lhs, execution_state rhs)
{
	return std::underlying_type_t<execution::execution_state>(lhs) ^ std::underlying_type_t<execution_state>(rhs);
}

std::underlying_type_t<execution::execution_state> execution::operator&= (execution_state lhs, execution_state rhs)
{
	return std::underlying_type_t<execution::execution_state>(lhs) & std::underlying_type_t<execution_state>(rhs);
}