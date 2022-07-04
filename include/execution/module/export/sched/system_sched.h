#pragma once
#include <modules/traits/modman_interface.h>
#include <execution/defines/export.h>

#include <execution/traits/sched/sched_traits.h>
#include <execution/sched/system_sched/syssched.h>

synapse_modules_component_interface
	synapse_execution_syssched_export
		();

void*
	synapse_execution_syssched_export_construct
		(va_list);

void
	synapse_execution_syssched_export_destruct
		(void*);

void*
	synapse_execution_syssched_export_duplicate
		(void*);