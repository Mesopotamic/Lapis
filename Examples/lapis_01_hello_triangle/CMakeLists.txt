cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
set(EXAMPLE_NAME "lapis_01_hello_triangle")

if(TARGET ${EXAMPLE_NAME})
	return()
endif()

# Since Lapis runs on a lot of different platforms, they might have different entry points
# instead of just main. For example, windows has winmain(). This is provided through a 
# cmake function declared in Lapis/Source/cmake which has been added to the module path
include(meso_cross_platform_executable)
meso_add_executable(${EXAMPLE_NAME} ${CMAKE_CURRENT_LIST_DIR}/lapis_01_hello_tringle.c)
meso_apply_example_target_settings(${EXAMPLE_NAME})

add_subdirectory(../.. lapis)
target_link_libraries(${EXAMPLE_NAME} PRIVATE lapis)
target_include_directories(${EXAMPLE_NAME} PRIVATE ${LAPIS_include_dirs})