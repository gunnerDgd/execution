#include <execution/export/io_sched/io_sched_init.h>
#include <execution/io_sched/io_sched_init.h>

synapse_execution_dll
    synapse_io_scheduler
        synapse_initialize_io_scheduler
            ()
{
    return
        synapse_execution_io_sched_initialize
            ();
}

synapse_execution_dll
    synapse_io_scheduler_task
        synapse_initialize_io_scheduler_task
            (void*  pIoMemory,
             size_t pIoMemorySize,
             void (*pIoCompletionRoutine)(size_t, void*), 
             void  *pIoCompletionParameter)
{
    return
        synapse_execution_io_task_initialize
            (pIoMemory, pIoMemorySize,
                pIoCompletionRoutine, pIoCompletionParameter);
}

synapse_execution_dll
    synapse_io_scheduler_task
        synapse_initialize_io_scheduler_task_from_existing
            (synapse_io_scheduler_task pIoTask,
             void*  pIoMemory, 
             size_t pIoMemorySize,
             void (*pIoCompletionRoutine)(size_t, void*), 
             void  *pIoCompletionParameter)
{
    return
        synapse_execution_io_task_initialize_from_existing
            (pIoTask, pIoMemory, pIoMemorySize,
                pIoCompletionRoutine, pIoCompletionRoutine);
}

synapse_execution_dll
    void
        synapse_cleanup_io_scheduler
            (synapse_io_scheduler pIoSched)
{
    synapse_execution_io_sched_cleanup
        (pIoSched);
}

synapse_execution_dll
    void
        synapse_cleanup_io_scheduler_task
            (synapse_io_scheduler_task pIoTask)
{
    synapse_execution_io_task_cleanup
        (pIoTask);
}