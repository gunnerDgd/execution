#pragma once
#include <executor/executor_concept.hpp>

namespace executor {

    template <typename Environment>
    class executor;

    template <typename Environment>
    class executor
    {
    public:
        using handle_t   = typename Environment::executor_handle  ;

    public:
        template <typename Launcher, typename... Args>
        executor(Launcher exec_launcher, Args... exec_args)
            : executor_previous(Environment::capture_execution(executor_previous)),
              executor_handle  (Environment::start_execution  (executor_previous, exec_launcher, exec_args...)) { }

        executor ()         { Environment::capture_execution(executor_handle); }
        ~executor()         { Environment::end_execution    (executor_handle); }

        handle_t& get_handle() { return                    executor_handle; }

    protected:
        handle_t executor_handle,
                 executor_previous; // Selective.
    };


}
