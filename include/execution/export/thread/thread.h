#include <execution/defines/export/export.h>
#include <execution/export/interface/thread/thread.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

synapse_execution_dll
    synapse_thread
        synapse_initialize_thread
            (size_t);

synapse_execution_dll
    synapse_thread
        synapse_initialize_thread_default
            ();

synapse_execution_dll
    void
        synapse_cleanup_thread
            (synapse_thread);

synapse_execution_dll
    void
        synapse_dispatch_task_to_thread
            (synapse_thread, void(*)(void*), void*);

synapse_execution_dll
    void
        synapse_wait_thread
            (synapse_thread);

synapse_execution_dll
    bool
        synapse_wait_thread_until
            (synapse_thread, uint32_t);