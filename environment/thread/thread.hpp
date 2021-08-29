#include <pthread.h>
#include <tuple>

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

    class thread
    {
    public:
        using executor_handle = pthread_t;

    public:
        template <typename Fp, typename... Farg>
        static executor_handle start_execution  (executor_handle& exec_prev, Fp exec_function, Farg... exec_argument);
        static void            end_execution    (executor_handle& exec)                 { pthread_cancel(exec); }
        
        static void            wait_execution   (executor_handle& exec)                 { pthread_join(exec, nullptr); }
        static void            capture_execution(executor_handle& exec)                 { exec = pthread_self(); }
    };
}
}

template <typename Fp, typename... Farg>
typename executor::environment::thread::executor_handle executor::environment::thread::start_execution(executor_handle& exec_prev, Fp exec_function, Farg... exec_argument)
{
    executor_handle                    thread_handle  ;
    thread_start_argument<Fp, Farg...> thread_argument(exec_function, exec_argument...);
    
    int       thread_res             = pthread_create(thread_handle, nullptr, thread_start_wrapper<Fp, Farg...>, (void*)&thread_argument);
    return    thread_handle;
}