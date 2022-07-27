#pragma once
#include <execution/io_sched/details/iosched_type.h>

void 
    __synapse_execution_io_sched_completion_routine_winsock
        (uint32_t, uint32_t, __synapse_execution_io_task*, uint32_t);

void
    __synapse_execution_io_sched_completion_routine
        (uint32_t, uint32_t, __synapse_execution_io_task*);


void
    __synapse_execution_io_sched_dispatch_tcp_recv
        (__synapse_execution_io_sched*,
            __synapse_execution_io_handle*,
                __synapse_execution_io_task*);
    
void
    __synapse_execution_io_sched_dispatch_tcp_send
        (__synapse_execution_io_sched*,
            __synapse_execution_io_handle*,
                __synapse_execution_io_task*);

void
    __synapse_execution_io_sched_dispatch_file_read
        (__synapse_execution_io_sched*,
            __synapse_execution_io_handle*,
                __synapse_execution_io_task*, size_t);
    
void
    __synapse_execution_io_sched_dispatch_file_write
        (__synapse_execution_io_sched*,
            __synapse_execution_io_handle*,
                __synapse_execution_io_task*, size_t);