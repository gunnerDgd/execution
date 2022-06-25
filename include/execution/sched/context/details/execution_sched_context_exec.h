#pragma once
#include <execution/sched/context/details/execution_sched_context_type.h>

void
__synapse_execution_sched_context_dispatch
	(__synapse_execution_sched_context*, __synapse_execution_sched_context_task*);

void
__synapse_execution_sched_context_execute_once
	(__synapse_execution_sched_context*);

void
__synapse_execution_sched_context_execute_multiple
	(__synapse_execution_sched_context*, size_t);