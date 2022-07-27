#pragma once
#include <execution/interface/sched/io_sched.h>

synapse_execution_io_sched
    synapse_execution_io_sched_initialize
        ();

synapse_execution_io_task
    synapse_execution_io_task_initialize
        (void*, size_t,
            void(*)(size_t, void*), void*);

synapse_execution_io_task
    synapse_execution_io_task_initialize_from_existing
        (synapse_execution_io_task, 
            void*, size_t,
                void(*)(size_t, void*), void*);

void
    synapse_execution_io_sched_cleanup
        (synapse_execution_io_sched);

void
    synapse_execution_io_task_cleanup
        (synapse_execution_io_task);