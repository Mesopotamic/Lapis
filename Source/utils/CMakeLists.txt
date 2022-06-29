cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(SOURCES ${CMAKE_CURRENT_LIST_DIR}/lapis_utils_common.c)

target_sources(lapis_utils PRIVATE ${SOURCES})