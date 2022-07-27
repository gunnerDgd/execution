#include <execution/export/io_sched/io_sched_manip.h>
#include <execution/io_sched/io_sched_manip.h>

synapse_execution_dll
    void
        synapse_dispath_file_read_to_io_scheduler
            (synapse_io_scheduler            pIoSched,
             synapse_io_schedule_handle_file pIoFile,
             synapse_execution_io_task       pIoTask, 
             size_t                          pIoOffset)
{
    synapse_execution_io_sched_dispatch_file_read
        (pIoSched, pIoFile, pIoTask, pIoOffset);
}

synapse_execution_dll
    void
        synapse_dispath_file_write_to_io_scheduler
            (synapse_io_scheduler            pIoSched,
             synapse_io_schedule_handle_file pIoFile,
             synapse_io_scheduler_task       pIoTask, 
             size_t                          pIoOffset)
{
    synapse_execution_io_sched_dispatch_file_write
        (pIoSched, pIoFile, pIoTask, pIoOffset);
}

synapse_execution_dll
    void
        synapse_dispath_tcp_receive_to_io_scheduler
            (synapse_io_scheduler           pIoSched,
             synapse_io_schedule_handle_tcp pIoTcp,
             synapse_io_scheduler_task      pIoTask)
{
    synapse_execution_io_sched_dispatch_tcp_recv
        (pIoSched, pIoTcp, pIoTask);
}

synapse_execution_dll
    void
        synapse_dispath_tcp_send_to_io_scheduler
            (synapse_io_scheduler           pIoSched,
             synapse_io_schedule_handle_tcp pIoTcp,
             synapse_io_scheduler_task      pIoTask)
{
    synapse_execution_io_sched_dispatch_tcp_send
        (pIoSched, pIoTcp, pIoTask);
}