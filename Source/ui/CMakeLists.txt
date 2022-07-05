cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# UI shouldn't have any backend specific differences 
# as the graphics backend should handle that
target_sources(lapis_ui PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/ui_common.c)