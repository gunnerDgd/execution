#pragma once
#include <execution/sched/system_sched/details/execution_sched_system_type.h>

__synapse_execution_sched_system*
__synapse_execution_sched_system_initialize
	(synapse_memory_pooling_dynamic_traits*);

void
__synapse_execution_sched_system_cleanup
	(__synapse_execution_sched_system*);