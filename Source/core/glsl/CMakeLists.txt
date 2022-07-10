cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

target_sources(lapis_core PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/glsl_core.h
	${CMAKE_CURRENT_LIST_DIR}/glsl_core_init.c
	${CMAKE_CURRENT_LIST_DIR}/glsl_core_context.c)

target_include_directories(lapis_core PRIVATE ${CMAKE_CURRENT_LIST_DIR})