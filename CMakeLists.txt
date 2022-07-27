cmake_minimum_required(VERSION 3.0)

project(
    synapse-execution
    VERSION 0.1.0
    LANGUAGES C
)

if(SYNAPSE_BUILD_STATIC_LIB)
    add_subdirectory(source/lib)
endif()

if(SYNAPSE_BUILD_SHARED_LIB)
    add_subdirectory(source/shared_lib)
endif()