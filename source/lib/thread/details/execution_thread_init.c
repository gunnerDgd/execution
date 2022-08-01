#include <execution/thread/details/execution_thread_init.h>
#include <synapse/memory/memory.h>

__synapse_execution_thread*
    __synapse_execution_thread_initialize
        (size_t pThreadQueueSize)
{
    __synapse_execution_thread*
        ptr_thread
            = synapse_system_allocate
                    (sizeof(__synapse_execution_thread));
    
    ptr_thread->hnd_thread_queue
        = synapse_initialize_mpmc_queue
                (pThreadQueueSize);
    ptr_thread->hnd_thread_execution_event
        = CreateEvent
                (NULL, FALSE, FALSE, NULL);
    ptr_thread->hnd_thread
        = _beginthreadex
                (0, 0, __synapse_execution_thread_loop,
                    ptr_thread, 0, 0);

    return
        ptr_thread;
}

void
    __synapse_execution_thread_loop
        (__synapse_execution_thread* pThread)
{
    __synapse_execution_thread_task
        *ptr_task;
    __synapse_execution_thread_loop_begin
        ptr_task
            = synapse_read_mpmc_queue
                    (pThread->hnd_thread_queue);
        
        if(!ptr_task) {
            WaitForSingleObject
                (pThread->hnd_thread_execution_event, INFINITE);
            continue;
        }
        
        if(!ptr_task->ptr_thread_task)
            break;
        
        ptr_task->ptr_thread_task
            (ptr_task->ptr_thread_task_parameter);
        
        synapse_system_deallocate
            (ptr_task);
    __synapse_execution_thread_loop_end
}

void
    __synapse_execution_thread_cleanup
        (__synapse_execution_thread* pThread)
{
    __synapse_execution_thread_task
        ptr_poison_pill
            = { .ptr_thread_task = 0 };
    
    synapse_write_mpmc_queue_until_success
        (pThread->hnd_thread_queue, &ptr_poison_pill);
    SetEvent
        (pThread->hnd_thread_execution_event);
    WaitForSingleObject
        (pThread->hnd_thread, INFINITE);
    
    synapse_system_deallocate
        (pThread);
}