#pragma once

#include <execution/defines/export/export.h>
#include <execution/export/interface/sched/io_sched.h>

synapse_execution_dll
    void
        synapse_dispath_file_read_to_io_scheduler
            (synapse_io_scheduler,
                synapse_io_schedule_handle_file,
                    synapse_execution_io_task, size_t);

synapse_execution_dll
    void
        synapse_dispath_file_write_to_io_scheduler
            (synapse_io_scheduler,
                synapse_io_schedule_handle_file,
                    synapse_io_scheduler_task, size_t);

synapse_execution_dll
    void
        synapse_dispath_tcp_receive_to_io_scheduler
            (synapse_io_scheduler,
                synapse_io_schedule_handle_tcp,
                    synapse_io_scheduler_task);

synapse_execution_dll
    void
        synapse_dispath_tcp_send_to_io_scheduler
            (synapse_io_scheduler,
                synapse_io_schedule_handle_tcp,
                    synapse_io_scheduler_task);