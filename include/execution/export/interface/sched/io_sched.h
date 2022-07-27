#pragma once
#include <execution/interface/sched/io_sched.h>

typedef synapse_execution_io_task
            synapse_io_scheduler_task;

typedef synapse_execution_io_handle_tcp
            synapse_io_schedule_handle_tcp;

typedef synapse_execution_io_handle_udp
            synapse_io_schedule_handle_udp;

typedef synapse_execution_io_handle_file
            synapse_io_schedule_handle_file;

typedef synapse_execution_io_sched
            synapse_io_scheduler;