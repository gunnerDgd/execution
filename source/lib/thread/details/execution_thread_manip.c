#include <execution/thread/details/execution_thread_manip.h>

void
    __synapse_execution_thread_dispatch
        (__synapse_execution_thread* pThread,
                void(*pThreadExec)(void*), void* pThreadParam)
{
    pThread->ptr_thread_exec
        = pThreadExec;
    pThread->ptr_thread_exec_param
        = pThreadParam;

    SetEvent
        (pThread->hnd_thread);
}

void
    __synapse_execution_thread_wait
        (__synapse_execution_thread* pThread)
{
    __synapse_execution_thread_wait_until
        (pThread, INFINITE);
}

bool
    __synapse_execution_thread_wait_until
        (__synapse_execution_thread* pThread, uint32_t pWaitTime)
{
    return
        (WaitForSingleObject
            (pThread->hnd_thread, pWaitTime) == WAIT_OBJECT_0)
                ? true : false;
}