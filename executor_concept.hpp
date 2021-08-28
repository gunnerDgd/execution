#include <type_traits>

namespace executor {

    template <typename T>
    concept bool FunctionType = std::is_function_v<T>;

    template <typename Environment>
    concept bool Switchable   = requires(typename Environment::executor_launcher l,
                                         typename Environment::executor_launcher r) { Environment::switch_execution(l, r); };

    template <typename Environment>
    concept bool Suspendable  = requires(typename Environment::executor_launcher l) { Environment::suspend_execution(l)  ; };

    template <typename Environment>
    concept bool Reenterable  = Switchable<Environment> && Suspendable<Environment>;
}