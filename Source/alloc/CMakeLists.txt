cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# Select the correct backend for the windowing system
# defined in ../cmake/meso_backend_selector.cmake
include(meso_backend_selector)
add_subdirectory(${meso_gfx_backend})

add_subdirectory(common)