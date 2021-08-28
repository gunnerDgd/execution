#include <executor/environment/thread/thread.hpp>
#include <executor/executor.hpp>

namespace executor {

    template <typename Fp>
    using thread = executor<Fp, environment::thread<Fp>>;
}