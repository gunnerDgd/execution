#include <execution/module/main.h>

#include <modules/modman/modman.h>
#include <modules/component/component.h>

#include <modules/component/manager/component_manager_init.h>
#include <modules/component/manager/component_manager_manip.h>

#include <string.h>

static synapse_execution_sched_traits
			__synapse_execution_module_sched_typedata;

synapse_execution_export
	void
		synapse_modules_initialize
			(synapse_modules_interface* pInterface)
{
	strcpy
		(pInterface->modules_name, "synapse-execution");
}

synapse_execution_export
	void
		synapse_modules_cleanup
			()
{
	
}

synapse_execution_export
	void
		synapse_execution_module_attach
			(synapse_modules_handle pHandle)
{
	synapse_modules_component_manager
		hnd_compmgr
			= synapse_modules_modman_module_retrieve_component_manager
					(pHandle);
	
	synapse_modules_component_manager_register_interface
		(hnd_compmgr, synapse_execution_syssched_export(), "system_sched",
				&__synapse_execution_module_sched_typedata);
}