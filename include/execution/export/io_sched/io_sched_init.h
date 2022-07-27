#pragma once

#include <execution/defines/export/export.h>
#include <execution/export/interface/sched/io_sched.h>

synapse_execution_dll
    synapse_io_scheduler
        synapse_initialize_io_scheduler
            ();

synapse_execution_dll
    synapse_io_scheduler_task
        synapse_initialize_io_scheduler_task
            (void*, size_t,
                void(*)(size_t, void*), void*);

synapse_execution_dll
    synapse_io_scheduler_task
        synapse_initialize_io_scheduler_task_from_existing
            (void*, size_t,
                void(*)(size_t, void*), void*);

synapse_execution_dll
    void
        synapse_cleanup_io_scheduler
            (synapse_io_scheduler);

synapse_execution_dll
    void
        synapse_cleanup_io_scheduler_task
            (synapse_io_scheduler_task);
