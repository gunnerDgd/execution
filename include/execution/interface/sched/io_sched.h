#pragma once
#include <execution/defines/handle/opaque_handle.h>

#include <stdint.h>
#include <stddef.h>

synapse_execution_opaque_declare
    (synapse_execution_io_task);

synapse_execution_opaque_declare
    (synapse_execution_io_handle_tcp);

synapse_execution_opaque_declare
    (synapse_execution_io_handle_udp);

synapse_execution_opaque_declare
    (synapse_execution_io_handle_file);

synapse_execution_opaque_declare
    (synapse_execution_io_sched);