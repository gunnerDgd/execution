#pragma once
#include <execution/sched/context/details/execution_sched_context_type.h>

__synapse_execution_sched_context_task*
__synapse_execution_sched_context_task_initialize
	(__synapse_execution_sched_context*, void(*)(synapse_context_default_entity, void*), void*);

void
__synapse_execution_sched_context_task_cleanup
	(__synapse_execution_sched_context*, __synapse_execution_sched_context_task*);