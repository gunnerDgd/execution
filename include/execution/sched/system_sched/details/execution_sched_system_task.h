#pragma once
#include <execution/sched/system_sched/details/execution_sched_system_type.h>

__synapse_execution_sched_task*
__synapse_execution_sched_system_task_initialize
	(__synapse_execution_sched_system*, void(*)(void*), void*);

void
__synapse_execution_sched_system_task_cleanup
	(__synapse_execution_sched_system*, __synapse_execution_sched_task*);