#include <executor/environment/branch/header/context.hpp>
#include <sys/mman.h>
#include <type_traits>

namespace executor    {
namespace environment {

    class branch
    {
    public:
        using executor_handle   = ::branch::context::context_entity*;

    public:
        template <typename Launcher, typename... Args>
        static executor_handle start_execution  (executor_handle prev, Launcher launcher, Args... args);
        static void            end_execution    (executor_handle handle)                               { delete handle; }
        
        static void            switch_execution (executor_handle prev, executor_handle next)           { ::branch::context::switch_to(*prev, *next); }
        static void            capture_execution(executor_handle& capture)                             { capture = new ::branch::context::context_entity; }
    };
}
}

template <typename Launcher, typename... Args>
typename executor::environment::branch::executor_handle executor::environment::branch::start_execution(executor_handle prev, Launcher launcher, Args... args)
{
    executor_handle exec_context    = new ::branch::context::context_entity;
    exec_context->stack_context.rsp = (uint64_t)mmap(nullptr, 4096, 
                                                     PROT_READ | PROT_WRITE | PROT_EXEC, 
                                                     MAP_ANONYMOUS | MAP_PRIVATE,
                                                     -1, 0);
    exec_context->stack_context.rbp = exec_context->stack_context.rsp + 4096;

    ::branch::context::execution_argument<Launcher, Args...> exec_arg;
    exec_arg.exec_function                                 = launcher;
    exec_arg.exec_argument                                 = std::forward_as_tuple(args...);

    ::branch::context::execute_to(*prev, *exec_context, exec_arg);
    return             exec_context;
}