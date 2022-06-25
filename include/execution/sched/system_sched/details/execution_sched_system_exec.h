#pragma once
#include <execution/sched/system_sched/details/execution_sched_system_type.h>

void
__synapse_execution_sched_system_dispatch
	(__synapse_execution_sched_system*, __synapse_execution_sched_task*);

void
__synapse_execution_sched_system_execute_once
	(__synapse_execution_sched_system*);

void
__synapse_execution_sched_system_execute_multiple
	(__synapse_execution_sched_system*, size_t);