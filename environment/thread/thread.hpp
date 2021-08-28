#include <pthread.h>

namespace executor    {
namespace environment {

    template <typename Fp, typename... Farg>
    struct thread_start_argument
    {
        thread_start_argument(Fp func, Farg... farg)
            : thread_function(func),
              thread_argument(std::forward_as_tuple(farg...)) { }

        Fp                  thread_function;
        std::tuple<Farg...> thread_argument;
    };

    template <typename Fp, typename... Farg>
    void*  thread_start_wrapper(void* context)
    {
        auto args = reinterpret_cast<thread_start_argument<Fp, Farg...>*>(context);
        std::apply (args->thread_function, args->thread_argument);

        pthread_exit(0);
    }

    template <typename Launcher>
    class thread
    {
    public:
        using executor_handle   = std::tuple<pthread_t, void*>;
        using executor_launcher = Launcher;

#define THREAD_GET_HANDLE(handle)   std::get<0>(handle)
#define THREAD_GET_ARGUMENT(handle) std::get<1>(handle)

    public:
        template <typename Fp, typename... Farg>
        static executor_handle start_execution  (Fp exec_function, Farg... exec_argument);
        static void            end_execution    (execution_handle& exec)                 { pthread_cancel(exec); delete THREAD_GET_ARGUMENT(exec); }
        
        static void            wait_execution   (execution_handle& exec)                 { pthread_join(THREAD_GET_HANDLE(exec)); }
    };
}
}

template <typename Fp, typename... Farg>
executor::environment::thread::executor_handle executor::environment::thread::start_execution(Fp exec_function, Farg... exec_argument)
{
    executor::environment::thread::executor_handle thread_handle;
    THREAD_GET_ARGUMENT(thread_handle)           = new thread_start_argument<Fp, Farg...>(exec_function, exec_argument...);

    int       thread_res   = pthread_create(&std::get<0>(thread_handle)        ,
                                            nullptr                            ,
                                            thread_start_wrapper<Fp, Farg...>  ,
                                            THREAD_GET_ARGUMENT(thread_handle));

    return    thread_handle;
}