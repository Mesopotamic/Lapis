cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
project(Lapis VERSION 0.1.0 LANGUAGES C)

# CMake used for every Mesopotamic project ========================

# There's two ways to build Mesopotamic projects. Either from 
# the Mesopotamic root directory, building everything together 
# or just building that individual project as a standalone.
# 
# The path to the project's dependencies are stored in CMake
# cache. So when building everything together you won't build
# multiple times. but it also allows projects to be built by 
# themselves without downloading all of Mesopotamic
set(MESO_LAPIS ${CMAKE_CURRENT_LIST_DIR} CACHE PATH "")
set(MESO_CMAKE ${CMAKE_CURRENT_LIST_DIR}/CMake CACHE PATH "")
set(MESO_SOLOMON ${CMAKE_CURRENT_LIST_DIR}/External/solomon CACHE PATH "")

# Add in the CMake helpers used by all mesopotamic projects
list(APPEND CMAKE_MODULE_PATH ${MESO_CMAKE})
include(Mesopotamic)

# Has the user specificed a static build of the library?
if(${MESO_BUILD_STATIC})
    set(BUILD_TYPE "")
else()
    set(BUILD_TYPE "SHARED")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Stop the Lapis project from getting added multiple times
if(TARGET Lapis)
    return()
endif()

# =================================================================
# Create the Lapis library
# Add the dependencies 
add_subdirectory(${MESO_SOLOMON} solomon)

# Add the lapis library and add it to the Meso project group
add_library(Lapis "Include/lapis/lapis.h" "Source/lapis.c")
meso_apply_target_settings(Lapis)

# Set the public lapis header locations
set(LAPIS_include_dirs "${CMAKE_CURRENT_LIST_DIR}/Include" CACHE PATH "Path to Lapis headers")
target_include_directories(Lapis PUBLIC ${SOLOMON_include_dirs})

# Add the rest of the Lapis source files
add_subdirectory(Source)

# =================================================================
# Add the Lapis examples
if(${MESO_BUILD_EXAMPLES})
    message(STATUS "Adding Lapis examples")
    add_subdirectory(Examples)
endif()
# =================================================================
meso_sort_target(Lapis)