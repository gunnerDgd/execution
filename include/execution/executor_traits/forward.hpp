#pragma once
#include <execution/forward.hpp>
#include <execution/executor_traits/executor_traits.hpp>

namespace execution {
	typedef execution::basic_executor<branch, executor_traits<branch>> executor;
}