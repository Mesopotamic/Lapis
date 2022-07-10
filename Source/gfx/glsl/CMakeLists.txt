cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

target_sources(lapis_gfx PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/glsl_gfx.h
	${CMAKE_CURRENT_LIST_DIR}/glsl_gfx_init.c
	${CMAKE_CURRENT_LIST_DIR}/glsl_gfx_target.c
	${CMAKE_CURRENT_LIST_DIR}/glsl_gfx_immediate.c)

target_include_directories(lapis_gfx PRIVATE ${CMAKE_CURRENT_LIST_DIR})