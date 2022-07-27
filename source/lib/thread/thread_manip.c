#include <execution/thread/thread_manip.h>
#include <execution/thread/details/execution_thread_manip.h>

void
    synapse_execution_thread_dispatch
        (synapse_execution_thread pThread,
            void(*pThreadExec)(void*), void* pThreadExecParam)
{
    __synapse_execution_thread_dispatch
        (synapse_execution_opaque_reference
            (pThread), pThreadExec, pThreadExecParam);
}

void
    synapse_execution_thread_wait
        (synapse_execution_thread pThread)
{
    __synapse_execution_thread_wait
        (synapse_execution_opaque_reference
            (pThread));
}

bool
    synapse_execution_thread_wait_until
        (synapse_execution_thread pThread, uint32_t pWaitTime)
{
    return
        __synapse_execution_thread_wait_until
            (synapse_execution_opaque_reference
                (pThread), pWaitTime);
}