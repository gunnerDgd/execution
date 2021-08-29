#include <type_traits>

namespace executor {

    template <typename T>
    concept bool FunctionType = std::is_function_v<T>;

    template <typename Environment>
    concept bool Switchable   = requires(typename Environment::executor_handle l,
                                         typename Environment::executor_handle r) { Environment::switch_execution(l, r); };
}