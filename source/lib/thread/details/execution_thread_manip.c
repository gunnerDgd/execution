#include <execution/thread/details/execution_thread_manip.h>
#include <synapse/memory/memory.h>

void
    __synapse_execution_thread_dispatch
        (__synapse_execution_thread* pThread,
                void(*pThreadExec)(void*), void* pThreadParam)
{
    __synapse_execution_thread_task*
        ptr_task
            = synapse_system_allocate
                    (sizeof(__synapse_execution_thread_task));

    synapse_write_mpmc_queue_until_success
        (pThread->hnd_thread_queue, ptr_task);
    SetEvent
        (pThread->hnd_thread_execution_event);
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