#pragma once
#include <execution/branch.hpp>

#include <execution/executor_traits/executor_traits.hpp>
#include <execution/executor_traits/container/queue.hpp>

namespace execution {
	typedef execution::basic_executor<branch, executor_traits<branch, queueing::queue<branch>>> executor;
}