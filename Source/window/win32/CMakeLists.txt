cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

target_sources(lapis_window PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/win32_window_init.c)