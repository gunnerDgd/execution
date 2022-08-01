#pragma once
#include <execution/interface/thread/thread.h>

synapse_execution_thread
    synapse_execution_thread_initialize
        (size_t);

synapse_execution_thread
    synapse_execution_thread_initialize_default
        ();

void
    synapse_execution_thread_cleanup
        (synapse_execution_thread);