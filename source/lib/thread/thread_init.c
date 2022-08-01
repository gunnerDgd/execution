#include <execution/thread/thread_init.h>
#include <execution/thread/details/execution_thread_init.h>

synapse_execution_thread
    synapse_execution_thread_initialize
        (size_t pThreadQueueSize)
{
    synapse_execution_opaque_init
        (synapse_execution_thread, hnd_thread,
            __synapse_execution_thread_initialize
                (pThreadQueueSize));
}

synapse_execution_thread
    synapse_execution_thread_initialize_default
        ()
{
    return
        synapse_execution_thread_initialize
            (__synapse_execution_thread_queue_default);
}
void
    synapse_execution_thread_cleanup
        (synapse_execution_thread pThread)
{
    __synapse_execution_thread_cleanup
        (synapse_execution_opaque_reference
            (pThread));
}