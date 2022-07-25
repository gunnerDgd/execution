#include <execution/io_sched/io_sched_init.h>
#include <execution/io_sched/details/iosched_init.h>

synapse_execution_io_sched
    synapse_execution_io_sched_initialize
        ()
{
    synapse_execution_opaque_init
        (synapse_execution_io_sched, hnd_io_sched,
            __synapse_execution_io_sched_initialize());
    
    return
        hnd_io_sched;
}

synapse_execution_io_task
    synapse_execution_io_task_initialize
        (void*  pIoMemory    , 
         size_t pIoMemorySize,
         void (*pIoCompletionRoutine)(size_t, void*), 
         void  *pIoCompletionRoutineParam)
{
    synapse_execution_opaque_init
        (synapse_execution_io_task, hnd_task,
            __synapse_execution_io_task_initialize
                (pIoMemory, pIoMemorySize,
                    pIoCompletionRoutine, pIoCompletionRoutineParam));
    
    return
        hnd_task;
}

synapse_execution_io_task
    synapse_execution_io_task_initialize_from_existing
        (synapse_execution_io_task pIoTask,
         void*  pIoMemory, 
         size_t pIoSize,
         void (*pIoCompletionRoutine)(size_t, void*), 
         void  *pIoCompletionRoutineParam)
{
    __synapse_execution_io_task_initialize_from_existing
        (synapse_execution_opaque_reference
            (pIoTask),
                pIoMemory, pIoSize,
                    pIoCompletionRoutine, pIoCompletionRoutineParam);

    return pIoTask;
}

void
    synapse_execution_io_sched_cleanup
        (synapse_execution_io_sched pIoSched)
{
    __synapse_execution_io_sched_cleanup
        (synapse_execution_opaque_reference
            (pIoSched));
}

void
    synapse_execution_io_task_cleanup
        (synapse_execution_io_task pIoTask)
{
    __synapse_execution_io_task_cleanup
        (synapse_execution_opaque_reference
            (pIoTask));
}