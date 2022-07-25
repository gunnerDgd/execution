#include <execution/io_sched/details/iosched_type.h>

void
    synapse_execution_io_sched_dispatch_file_read
        (synapse_execution_io_sched,
            synapse_execution_io_handle_file,
                synapse_execution_io_task, size_t);

void
    synapse_execution_io_sched_dispatch_file_write
        (synapse_execution_io_sched,
            synapse_execution_io_handle_file,
                synapse_execution_io_task, size_t);

void
    synapse_execution_io_sched_dispatch_tcp_recv
        (synapse_execution_io_sched,
            synapse_execution_io_handle_tcp,
                synapse_execution_io_task);

void
    synapse_execution_io_sched_dispatch_tcp_send
        (synapse_execution_io_sched,
            synapse_execution_io_handle_tcp,
                synapse_execution_io_task);