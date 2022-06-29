#pragma once

#define synapse_execution_opaque_declare(pName)\
	typedef struct pName { void* opaque; } pName;

#define synapse_execution_opaque_reference(pObject)\
	(pObject.opaque)

#define synapse_execution_opaque_cast(pObject, pType)\
	((pType)(pObject.opaque))

#define synapse_execution_opaque_init(pObject, pName, pValue)\
	pObject pName = { .opaque = pValue }

#define synapse_execution_opaque_valid(pObject)\
	((pObject.opaque) != NULL)