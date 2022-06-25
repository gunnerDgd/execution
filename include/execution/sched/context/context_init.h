#pragma once
#include <execution/sched/context/context_type.h>

synapse_execution_sched_context
synapse_execution_sched_context_initialize
	(synapse_memory_pooling_dynamic_traits*, synapse_execution_sched_queue_entity*);

void
synapse_execution_sched_context_cleanup
	(synapse_execution_sched_context);