cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

target_sources(lapis_alloc PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/common_alloc.h
	${CMAKE_CURRENT_LIST_DIR}/common_alloc.c)

target_include_directories(lapis_alloc PRIVATE ${CMAKE_CURRENT_LIST_DIR})