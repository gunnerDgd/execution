#pragma once
#include <execution/sched/system_sched/syssched_type.h>

synapse_execution_export
void
synapse_execution_sched_system_dispatch
	(synapse_execution_sched_system, synapse_execution_sched_system_task);

synapse_execution_export
synapse_execution_sched_system_task
synapse_execution_sched_system_dispatch_from_proc
	(synapse_execution_sched_system, void(*)(void*), void*);

synapse_execution_export
void
synapse_execution_sched_system_execute_once
	(synapse_execution_sched_system);

synapse_execution_export
void
synapse_execution_sched_system_execute_multiple
	(synapse_execution_sched_system, size_t);