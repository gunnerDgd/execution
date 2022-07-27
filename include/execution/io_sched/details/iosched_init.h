#pragma once
#include <execution/io_sched/details/iosched_type.h>

__synapse_execution_io_sched*
    __synapse_execution_io_sched_initialize 
        ();

__synapse_execution_io_task*
    __synapse_execution_io_task_initialize
        (void*, size_t,
            void(*)(size_t, void*), void*);

__synapse_execution_io_task*
    __synapse_execution_io_task_initialize_from_existing
        (__synapse_execution_io_task*,
            void*, size_t,
                void(*)(size_t, void*), void*);

void
    __synapse_execution_io_sched_cleanup
        (__synapse_execution_io_sched*);

void
    __synapse_execution_io_task_cleanup
        (__synapse_execution_io_task*);