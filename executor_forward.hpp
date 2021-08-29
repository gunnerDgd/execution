#include <executor/environment/thread/thread.hpp>
#include <executor/environment/branch/branch.hpp>

#include <executor/executor.hpp>

namespace executor {

    using thread = executor<environment::thread>;
    using branch = executor<environment::branch>;
}