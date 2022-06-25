#include <execution/sched/context/context_exec.h>
#include <execution/sched/context/details/execution_sched_context_exec.h>

 void
synapse_execution_sched_context_dispatch
	(synapse_execution_sched_context pSched, synapse_execution_sched_context_task pTask)
 {
	__synapse_execution_sched_context_dispatch
		(synapse_execution_opaque_reference(pSched),
		 synapse_execution_opaque_reference(pTask));
 }

void
synapse_execution_sched_context_execute_once
	(synapse_execution_sched_context pSched)
{
	__synapse_execution_sched_context_execute_once
		(synapse_execution_opaque_reference(pSched));
}

void
synapse_execution_sched_context_execute_multiple
	(synapse_execution_sched_context pSched, size_t pCount)
{
	__synapse_execution_sched_context_execute_multiple
		(synapse_execution_opaque_reference(pSched), pCount);
}