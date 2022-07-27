#include <execution/thread/details/execution_thread_init.h>
#include <synapse/memory/memory.h>

__synapse_execution_thread*
    __synapse_execution_thread_initialize
        ()
{
    __synapse_execution_thread*
        ptr_thread
            = synapse_system_allocate
                    (sizeof(__synapse_execution_thread));
    
    ptr_thread->flag_thread_execution
        = true;
    ptr_thread->ptr_thread_exec
        = NULL;
    ptr_thread->ptr_thread_exec_param
        = NULL;

    ptr_thread->hnd_thread_execution_event
        = CreateEvent
                (NULL, FALSE, FALSE, NULL);
    ptr_thread->hnd_thread
        = _beginthreadex
                (0, 0, ptr_thread->ptr_thread_exec,
                    ptr_thread, 0, 0);

    return
        ptr_thread;
}

void
    __synapse_execution_thread_loop
        (__synapse_execution_thread* pThread)
{
    while
        (pThread->flag_thread_execution
            != __synapse_execution_thread_state_stopped)
    {
        WaitForSingleObject
            (pThread->hnd_thread_execution_event,
                INFINITE);
        
        if(pThread->hnd_thread_execution_event)
            pThread->ptr_thread_exec
                (pThread->ptr_thread_exec_param);
    }
}

void
    __synapse_execution_thread_cleanup
        (__synapse_execution_thread* pThread)
{
    pThread->ptr_thread_exec
        = NULL;
    InterlockedExchange8
        (pThread->flag_thread_execution,
            __synapse_execution_thread_state_stopped);
    
    SetEvent
        (pThread->hnd_thread_execution_event);
    WaitForSingleObject
        (pThread->hnd_thread, INFINITE);
    
    synapse_system_deallocate
        (pThread);
}