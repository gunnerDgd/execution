#include <execution/io_sched/io_sched_manip.h>
#include <execution/io_sched/details/iosched_manip.h>

void
    synapse_execution_io_sched_dispatch_file_read
        (synapse_execution_io_sched       pIoSched,
         synapse_execution_io_handle_file pFile,
         synapse_execution_io_task        pIoTask, 
         size_t                           pIoOffset)
{
    __synapse_execution_io_sched_dispatch_file_read
        (synapse_execution_opaque_reference
            (pIoSched),
         synapse_execution_opaque_reference
            (pFile),
         synapse_execution_opaque_reference
            (pIoTask), pIoOffset);
}

void
    synapse_execution_io_sched_dispatch_file_write
        (synapse_execution_io_sched       pIoSched,
         synapse_execution_io_handle_file pFile,
         synapse_execution_io_task        pIoTask, 
         size_t                           pIoOffset)
{
    __synapse_execution_io_sched_dispatch_file_write
        (synapse_execution_opaque_reference
            (pIoSched),
         synapse_execution_opaque_reference
            (pFile),
         synapse_execution_opaque_reference
            (pIoTask), pIoOffset);
}

void
    synapse_execution_io_sched_dispatch_tcp_recv
        (synapse_execution_io_sched      pIoSched,
         synapse_execution_io_handle_tcp pTcp,
         synapse_execution_io_task       pIoTask)
{
    __synapse_execution_io_sched_dispatch_tcp_recv
        (synapse_execution_opaque_reference
            (pIoSched),
         synapse_execution_opaque_reference
            (pTcp),
         synapse_execution_opaque_reference
            (pIoTask));
}

void
    synapse_execution_io_sched_dispatch_tcp_send
        (synapse_execution_io_sched      pIoSched,
         synapse_execution_io_handle_tcp pTcp,
         synapse_execution_io_task       pIoTask)
{
    __synapse_execution_io_sched_dispatch_tcp_send
        (synapse_execution_opaque_reference
            (pIoSched),
         synapse_execution_opaque_reference
            (pTcp),
         synapse_execution_opaque_reference
            (pIoTask));
}