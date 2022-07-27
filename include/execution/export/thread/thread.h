#include <execution/export/interface/thread/thread.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

synapse_thread
    synapse_initialize_thread
        ();

void
    synapse_cleanup_thread
        (synapse_thread);

void
    synapse_dispatch_to_thread
        (synapse_thread, void(*)(void*), void*);

void
    synapse_wait_thread
        (synapse_thread);

bool
    synapse_wait_thread_until
        (synapse_thread, uint32_t);