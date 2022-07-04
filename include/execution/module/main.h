#pragma once
#include <modules/traits/modman_interface.h>
#include <execution/defines/export.h>
#include <execution/module/export/sched/system_sched.h>

synapse_execution_export
	void
		synapse_modules_initialize
			(synapse_modules_interface*);

synapse_execution_export
	void
		synapse_modules_cleanup
			();

synapse_execution_export
	void
		synapse_execution_module_attach
			(synapse_modules_handle);