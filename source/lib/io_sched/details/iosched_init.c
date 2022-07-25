#include <execution/io_sched/details/iosched_type.h>
#include <synapse/memory/memory.h>

#include <networking/tcp/details/tcp_init.h>
#include <filesystem/file/details/fs_file_init.h>

__synapse_execution_io_sched*
    __synapse_execution_io_sched_initialize 
        ()
{
    __synapse_execution_io_sched*
        ptr_io_sched
            = synapse_system_allocate
                    (sizeof(__synapse_execution_io_sched));
    
    ptr_io_sched->hnd_io_sched
        = CreateIoCompletionPort
                (INVALID_HANDLE_VALUE, 0, ptr_io_sched, 0);
                
    return
        ptr_io_sched;
}

__synapse_execution_io_task*
    __synapse_execution_io_task_initialize
        (void*  pIoMemory, 
         size_t pIoSize  , 
         void (*pIoCompletionRoutine)(size_t, void*), 
         void*  pIoCompletionRoutineParam)
{
    __synapse_execution_io_task*
        ptr_task
            = synapse_system_allocate
                    (sizeof(__synapse_execution_io_task));
    
    ptr_task->ptr_completion_routine
        = pIoCompletionRoutine;
    ptr_task->ptr_completion_routine_parameter
        = pIoCompletionRoutineParam;

    ptr_task->hnd_io_task.hEvent
        = CreateEvent(NULL, FALSE, FALSE, NULL);
    ptr_task->ptr_io_task_memory
        = pIoMemory;
    ptr_task->size_io_task_memory
        = pIoSize;
    
    return
        ptr_task;
}

__synapse_execution_io_task*
    __synapse_execution_io_task_initialize_from_existing
        (__synapse_execution_io_task* pIoTask,
         void*  pIoMemory, 
         size_t pIoSize,
         void (*pIoCompletionRoutine)(size_t, void*), 
         void*  pIoCompletionRoutineParam)
{
    pIoTask->ptr_completion_routine
        = pIoCompletionRoutine;
    pIoTask->ptr_completion_routine_parameter
        = pIoCompletionRoutineParam;
    
    pIoTask->ptr_io_task_memory
        = pIoMemory;
    pIoTask->size_io_task_memory
        = pIoSize;
    
    return
        pIoTask;
}

void
    __synapse_execution_io_sched_cleanup
        (__synapse_execution_io_sched* pIoSched)
{
    CloseHandle
        (pIoSched->hnd_io_sched);
    synapse_system_deallocate
        (pIoSched);
}

void
    __synapse_execution_io_task_cleanup
        (__synapse_execution_io_task* pIoTask)
{
    CloseHandle
        (pIoTask->hnd_io_task.hEvent);
    synapse_system_deallocate
        (pIoTask);
}