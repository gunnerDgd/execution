#pragma once
#include <execution/io_sched/details/iosched_type.h>

__synapse_execution_io_handle*
    __synapse_execution_io_handle_initialize_from_tcp
        (__synapse_execution_io_sched*, __synapse_networking_tcp*);

__synapse_execution_io_handle*
    __synapse_execution_io_handle_initialize_from_file
        (__synapse_execution_io_sched*, __synapse_filesystem_file*);

void
    __synapse_execution_io_handle_cleanup_from_tcp
        (__synapse_execution_io_handle*);

void
    __synapse_execution_io_handle_cleanup_from_file
        (__synapse_execution_io_handle*);