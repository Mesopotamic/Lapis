cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

add_executable(lapis_01_hello_triangle
	${CMAKE_CURRENT_LIST_DIR}/lapis_01_hello_tringle.c)
meso_apply_example_target_settings(lapis_01_hello_triangle)

add_subdirectory(../.. Lapis)
target_link_libraries(lapis_01_hello_triangle PRIVATE Lapis)
target_include_directories(lapis_01_hello_triangle PRIVATE ${LAPIS_include_dirs})