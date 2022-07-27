#include <execution/export/thread/thread.h>

#include <execution/thread/thread_init.h>
#include <execution/thread/thread_manip.h>

synapse_thread
    synapse_initialize_thread
        ()
{
    return
        synapse_execution_thread_initialize
            ();
}

void
    synapse_cleanup_thread
        (synapse_thread pThread)
{
    synapse_execution_thread_cleanup
        (pThread);
}

void
    synapse_dispatch_to_thread
        (synapse_thread pThread, 
            void(*pThreadExec)(void*), void* pThreadParam)
{
    synapse_execution_thread_dispatch
        (pThread, pThreadExec, pThreadParam);
}

void
    synapse_wait_thread
        (synapse_thread pThread)
{
    synapse_wait_thread
        (pThread);
}

bool
    synapse_wait_thread_until
        (synapse_thread pThread, uint32_t pWaitTime)
{
    return
        synapse_execution_thread_wait_until
            (pThread, pWaitTime);
}