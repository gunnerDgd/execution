#include <execution/api_export/system_sched/api_syssched.h>
#include <execution/sched/system_sched/syssched.h>

static synapse_execution_sched_system
	__apiexport_sched;

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

	__apiexport_sched
		= synapse_execution_sched_system_initialize
			();
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
	(synapse_modules_handle pModule, synapse_execution_sched_traits* pTraits)
{
	pTraits->dispatch
		= &synapse_execution_sched_system_dispatch;
	pTraits->execute_once
		= &synapse_execution_sched_system_execute_once;
	pTraits->execute_multuple
		= &synapse_execution_sched_system_execute_multiple;
	pTraits->hnd_sched.opaque
		= __apiexport_sched.opaque;
}

_declspec(dllexport)
void synapse_execution_syssched_api_detach
	(synapse_modules_handle pModule, synapse_execution_sched_traits* pTraits)
{
	synapse_execution_sched_system_cleanup
		(__apiexport_sched);
}

_declspec(dllexport)
void synapse_execution_syssched_api_reload
	(synapse_modules_handle, synapse_execution_sched_traits*);