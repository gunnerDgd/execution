#include <execution/sched/context/details/execution_sched_context_exec.h>

void
__synapse_execution_sched_context_do_execute
	(synapse_context_default_entity pContext, void* pTask)
{
	__synapse_execution_sched_context_task* ptr_task
		= pTask;

	ptr_task->task_exec_status
		= __synapse_execution_sched_context_task_running;

	ptr_task->task_exec
		(pContext, ptr_task->task_exec_param);

	ptr_task->task_exec_status
		= __synapse_execution_sched_context_task_ended;
}

void
__synapse_execution_sched_context_dispatch
	(__synapse_execution_sched_context		*pSched,
	 __synapse_execution_sched_context_task *pTask)
{
	pTask->task_exec_status
		= __synapse_execution_sched_context_task_standby;
	pTask->hnd_context_loop 
		= synapse_context_default_execute_from
			(pTask->hnd_context_this, 
			&__synapse_execution_sched_context_do_execute, 
			 pTask);

	pTask->hnd_queue_entity = 
		pSched->ptr_queue->enqueue_front
			(pSched->ptr_queue->hnd_queue, pTask, sizeof(__synapse_execution_sched_context_task));
}

void
__synapse_execution_sched_context_execute_once
	(__synapse_execution_sched_context* pSched)
{
	__synapse_execution_sched_context_task* ptr_task
		= pSched->ptr_queue->retrieve_pointer 
			(pSched->ptr_queue->dequeue_front(pSched->ptr_queue->hnd_queue));

	synapse_context_default_switch_to
		(ptr_task->hnd_context_loop, ptr_task->hnd_context_this);

	if (ptr_task->task_exec_status != __synapse_execution_sched_context_task_ended)
		return;

	ptr_task->task_exec
		= NULL;
	ptr_task->task_exec_param
		= NULL;
	ptr_task->hnd_context_this
		= synapse_context_default_initialize_from_existing(ptr_task->hnd_context_this);
	
	pSched->ptr_mpool->deallocate
		(pSched->ptr_mpool->hnd_traits, ptr_task->hnd_mpool_chunk);
}

void
__synapse_execution_sched_context_execute_multiple
	(__synapse_execution_sched_context* pSched, size_t pCount)
{
	while (--pCount)
		__synapse_execution_sched_context_execute_once(pSched);
}