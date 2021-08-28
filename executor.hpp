#include <executor/executor_concept.hpp>

namespace executor {

    template <typename Launcher , typename Environment>
    class executor;

    template <FunctionType Launcher, typename Environment>
    class executor
    {
    public:
        using handle_t   = Environment::executor_handle  ;
        using launcher_t = Environment::executor_launcher;

    public:
        template <typename... Args>
        executor(Launcher exec_launcher, Args... exec_args)
            : executor_handle(Environment::start_execution(exec_launcher, exec_args...)) { }

        void end () { Environment::end_execution (executor_handle); } // Destroy Handle and Return All Resources Binded In Handle.
        void wait() { Environment::wait_execution(executor_handle); }

    protected:
        handle_t executor_handle;
    };

    template <typename Launcher, Reenterable Environment>
    class executor
    {
    public:
        using handle_t   = Environment::executor_handle  ;
        using launcher_t = Environment::executor_launcher;

    public:
        template <typename... Args>
        executor(Launcher exec_launcher, Args... exec_args)
            : executor_handle(Environment::start_execution(exec_launcher, exec_args...)) { }

        //end() : Destroy Handle and Return All Resources Binded In Handle. 
        void end      () { Environment::end_execution(executor_handle); }
        void switch_to()
    };
}
