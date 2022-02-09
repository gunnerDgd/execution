#pragma once
#include <execution/forward.hpp>
#include <execution/executor_traits/executor_traits.hpp>

#include <execution/executor_traits/container/std_list.hpp>

namespace execution {
	typedef execution::basic_executor<branch, executor_traits<branch, queueing::std_list<branch>>> executor;
}