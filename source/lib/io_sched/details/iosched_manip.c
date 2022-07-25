#include <execution/io_sched/details/iosched_manip.h>

void 
    __synapse_execution_io_sched_completion_routine_winsock
        (uint32_t                     pError, 
         uint32_t                     pIoCompletionSize, 
         __synapse_execution_io_task* pIoTask, 
         uint32_t                     pIoFlag)
{
    pIoTask->ptr_completion_routine
        (pIoCompletionSize, 
                pIoTask->ptr_completion_routine_parameter);
}

void
    __synapse_execution_io_sched_completion_routine
        (uint32_t                     pError, 
         uint32_t                     pIoCompletionSize, 
         __synapse_execution_io_task* pIoTask)
{
    pIoTask->ptr_completion_routine
        (pIoCompletionSize,
            pIoTask->ptr_completion_routine_parameter);
}

void
    __synapse_execution_io_sched_dispatch_tcp_recv
        (__synapse_execution_io_sched*  pIoSched,
         __synapse_execution_io_handle* pIoHandle,
         __synapse_execution_io_task*   pIoTask)
{
    WSARecv
        (pIoHandle->ptr_io_handle_tcp,
            &pIoTask->hnd_network_buffer, 1,
                &pIoTask->size_io_task_completion,
                    0, &pIoTask->hnd_io_task,
                        &__synapse_execution_io_sched_completion_routine_winsock);
}
    
void
    __synapse_execution_io_sched_dispatch_tcp_send
        (__synapse_execution_io_sched*  pIoSched ,
         __synapse_execution_io_handle* pIoHandle,
         __synapse_execution_io_task*   pIoTask)
{
    WSASend
        (pIoHandle->ptr_io_handle_tcp,
            &pIoTask->hnd_network_buffer, 1,
                &pIoTask->size_io_task_completion,
                    0, &pIoTask->hnd_io_task,
                        &__synapse_execution_io_sched_completion_routine_winsock);
}

void
    __synapse_execution_io_sched_dispatch_file_read
        (__synapse_execution_io_sched*  pIoSched ,
         __synapse_execution_io_handle* pIoHandle,
         __synapse_execution_io_task*   pIoTask, 
         size_t                         pIoOffset)
{
    pIoTask->hnd_io_task.Pointer
        = pIoOffset;
    ReadFileEx
        (pIoHandle->ptr_io_handle_file,
            pIoTask->ptr_io_task_memory,
                pIoTask->size_io_task_memory,
                    &pIoTask->hnd_io_task,
                        &__synapse_execution_io_sched_completion_routine);
}
    
void
    __synapse_execution_io_sched_dispatch_file_write
        (__synapse_execution_io_sched*  pIoSched,
         __synapse_execution_io_handle* pIoHandle,
         __synapse_execution_io_task*   pIoTask  , 
         size_t                         pIoOffset)
{
    pIoTask->hnd_io_task.Pointer
        = pIoOffset;
    WriteFileEx
        (pIoHandle->ptr_io_handle_file,
            pIoTask->ptr_io_task_memory,
                pIoTask->size_io_task_memory,
                    &pIoTask->hnd_io_task,
                        &__synapse_execution_io_sched_completion_routine);
}