#include <execution/defines/export/export.h>
#include <execution/export/interface/sched/io_sched.h>

#include <synapse/filesystem/interface/file/file.h>
#include <synapse/networking/interface/tcp/tcp.h>

synapse_execution_dll
    synapse_io_schedule_handle_file
        synapse_initialize_io_handle_from_file
            (synapse_execution_io_sched, synapse_file_aio);

synapse_execution_dll
    synapse_io_schedule_handle_tcp
        synapse_initialize_io_handle_from_tcp
            (synapse_execution_io_sched, synapse_tcp_aio);

synapse_execution_dll
    void
        synapse_cleanup_io_handle_file
            (synapse_io_schedule_handle_file);

synapse_execution_dll
    void
        synapse_cleanup_io_handle_tcp
            (synapse_io_schedule_handle_tcp);