#include <execution/sched/system_sched/syssched_exec.h>

#include <execution/sched/system_sched/details/execution_sched_system_exec.h>
#include <execution/sched/system_sched/details/execution_sched_system_task.h>

void
synapse_execution_sched_system_dispatch
	(synapse_execution_sched_system pSched, synapse_execution_sched_system_task pTask)
{
	__synapse_execution_sched_system_dispatch
		(synapse_execution_opaque_reference(pSched),
		 synapse_execution_opaque_reference(pTask));
}

void
synapse_execution_sched_system_execute_once
	(synapse_execution_sched_system pSched)
{
	__synapse_execution_sched_system_execute_once
		(synapse_execution_opaque_reference(pSched));
}

void
synapse_execution_sched_system_execute_multiple
	(synapse_execution_sched_system pSched, size_t pCount)
{
	__synapse_execution_sched_system_execute_multiple
		(synapse_execution_opaque_reference(pSched), pCount);
}