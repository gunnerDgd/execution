#include <executor/environment/branch/context.hpp>

namespace executor {

    template <typename Launcher, typename... Args>
    class branch_handle : public branch::execution_wrapper
    {
    public:
        void execute()
    protected:
        std::tuple<Args...> branch_argument;
    };

    template <typename Launcher>
    class branch
    {
    public:
        using executor_handle   = Launcher;
        using executor_launcher = Launcher;
    };
}