#pragma once
#include <execution/sched/system_sched/syssched_type.h>

synapse_execution_sched_system_task
synapse_execution_sched_system_task_initialize
	(synapse_execution_sched_system, void(*)(void*), void*);

void
synapse_execution_sched_system_task_cleanup
	(synapse_execution_sched_system, synapse_execution_sched_system_task);