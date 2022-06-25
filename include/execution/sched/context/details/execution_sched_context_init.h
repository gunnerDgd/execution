#pragma once
#include <execution/sched/context/details/execution_sched_context_type.h>

__synapse_execution_sched_context*
__synapse_execution_sched_context_initialize
	(synapse_memory_pooling_dynamic_traits*, synapse_execution_sched_queue_traits*);

void
__synapse_execution_sched_context_cleanup
	(__synapse_execution_sched_context*);