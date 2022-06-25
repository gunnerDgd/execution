#pragma once
#include <execution/sched/context/context_type.h>
#include <stdint.h>

void
synapse_execution_sched_context_dispatch
	(synapse_execution_sched_context, synapse_execution_sched_context_task);

void
synapse_execution_sched_context_execute_once
	(synapse_execution_sched_context);

void
synapse_execution_sched_context_execute_multiple
	(synapse_execution_sched_context, size_t);