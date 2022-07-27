#pragma once

#include <execution/interface/sched/io_sched.h>

#include <synapse/filesystem/interface/file/file.h>
#include <synapse/networking/interface/tcp/tcp.h>

synapse_execution_io_handle_file
    synapse_execution_io_handle_initialize_from_file
        (synapse_execution_io_sched, synapse_file_aio);

synapse_execution_io_handle_tcp
    synapse_execution_io_handle_initialize_from_tcp
        (synapse_execution_io_sched, synapse_tcp_aio);

void
    synapse_execution_io_handle_file_cleanup
        (synapse_execution_io_handle_file);

void
    synapse_execution_io_handle_tcp_cleanup
        (synapse_execution_io_handle_tcp);