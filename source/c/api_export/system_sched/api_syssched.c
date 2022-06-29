#include <execution/api_export/system_sched/api_syssched.h>
#include <execution/sched/system_sched/syssched.h>

#include <stdlib.h>

synapse_execution_sched_traits*
synapse_execution_syssched_api_initialize
	(synapse_memory_pooling_dynamic_traits* pMpool)
{
	synapse_execution_sched_traits* ptr_traits
		= malloc(sizeof(synapse_execution_sched_traits));

	synapse_execution_sched_system ptr_sched
		= synapse_execution_sched_system_initialize
			(pMpool);
	ptr_traits->hnd_sched.opaque
		= ptr_sched.opaque;

	ptr_traits->dispatch
		= &synapse_execution_sched_system_dispatch;
	ptr_traits->execute_once
		= &synapse_execution_sched_system_execute_once;
	ptr_traits->execute_multiple
		= &synapse_execution_sched_system_execute_multiple;

	return ptr_traits;
}

void
synapse_execution_syssched_api_cleanup
	(synapse_execution_sched_traits* pTraits)
{
	synapse_execution_sched_system ptr_sched
		= { .opaque = pTraits->hnd_sched.opaque };

	synapse_execution_sched_system_cleanup
		(ptr_sched);
	free
		(pTraits);
}

_declspec(dllexport)
void synapse_module_initialize
	(synapse_modules_interface* pInterface)
{
	pInterface->attach
		= &synapse_execution_syssched_api_attach;
	pInterface->detach
		= &synapse_execution_syssched_api_detach;
	pInterface->reload
		= &synapse_execution_syssched_api_reload;
}

_declspec(dllexport)
void synapse_module_cleanup()
{

}

_declspec(dllexport)
void synapse_module_entry
	(synapse_modules_handle);

_declspec(dllexport)
void synapse_execution_syssched_api_attach
	(synapse_modules_handle pModule, synapse_api_syssched* pTraits)
{
	pTraits->initialize
		= &synapse_execution_syssched_api_initialize;
	pTraits->cleanup
		= &synapse_execution_syssched_api_cleanup;
}

_declspec(dllexport)
void synapse_execution_syssched_api_detach
	(synapse_modules_handle pModule, synapse_api_syssched* pTraits)
{
}

_declspec(dllexport)
void synapse_execution_syssched_api_reload
	(synapse_modules_handle pModule, synapse_api_syssched* pTraits) {}

