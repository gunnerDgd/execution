cmake_minimum_required(VERSION 3.0)

project(
    synapse-execution-lib
    VERSION 0.1.0
    LANGUAGES C
)

file(
    GLOB_RECURSE
    src_synapse_execution_lib
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(
    synapse_execution_lib
    STATIC
    ${src_synapse_execution_lib}
)

target_include_directories(
    synapse_execution_lib
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/submodules/synapse-networking/include
    ${CMAKE_SOURCE_DIR}/submodules/synapse-filesystem/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)