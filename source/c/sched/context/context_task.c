#include <execution/sched/context/context_task.h>
#include <execution/sched/context/details/execution_sched_context_task.h>

synapse_execution_sched_context_task
synapse_execution_sched_context_task_initialize
	(synapse_execution_sched_context pSched, 
	 void(*pTaskExec)(synapse_context_default_entity, void*), 
	 void *pTaskParam)
{
	synapse_execution_opaque_init
		(synapse_execution_sched_context_task,
		 ptr_task,
		 __synapse_execution_sched_context_task_initialize
			(synapse_execution_opaque_reference(pSched), pTaskExec, pTaskParam)
		);

	return
		ptr_task;
}

void
synapse_execution_sched_context_task_cleanup
	(synapse_execution_sched_context pSched,
	 synapse_execution_sched_context_task pTask)
{
	__synapse_execution_sched_context_task_cleanup
	   (synapse_execution_opaque_reference(pSched),
		synapse_execution_opaque_reference(pTask));
}