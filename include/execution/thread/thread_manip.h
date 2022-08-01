#pragma once
#include <execution/interface/thread/thread.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void
    synapse_execution_thread_dispatch
        (synapse_execution_thread, void(*)(void*), void*);

void
    synapse_execution_thread_wait
        (synapse_execution_thread);

bool
    synapse_execution_thread_wait_until
        (synapse_execution_thread, uint32_t);