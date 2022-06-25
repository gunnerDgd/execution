#pragma once
#include <execution/sched/system_sched/syssched_type.h>

void
synapse_execution_sched_system_dispatch
	(synapse_execution_sched_system, synapse_execution_sched_system_task);

void
synapse_execution_sched_system_execute_once
	(synapse_execution_sched_system);

void
synapse_execution_sched_system_execute_multiple
	(synapse_execution_sched_system, size_t);