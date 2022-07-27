cmake_minimum_required(VERSION 3.0)

project(
    synapse-execution-dll
    VERSION 0.1.0
    LANGUAGES C
)

file(
    GLOB_RECURSE
    src_synapse_execution_dll
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(
    synapse_execution_dll
    SHARED
    ${src_synapse_execution_dll}
)

target_include_directories(
    synapse_execution_dll
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_compile_options(
    synapse_execution_dll
    PUBLIC
    /Dsynapse_execution_export_mode
)

target_link_libraries(
    synapse_execution_dll
    ws2_32
    synapse_execution_lib
    synapse_networking_lib
    synapse_filesystem_lib
    synapse_memory_dll
)