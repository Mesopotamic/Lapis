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

# Add in the CMake helpers used by all mesopotamic projects
list(APPEND CMAKE_MODULE_PATH ${MESO_CMAKE})
include(Mesopotamic)

# Stop the Lapis project from getting added multiple times
if(TARGET lapis)
    return()
endif()

# =================================================================
# Create the Lapis libraries

# Set the public lapis header locations
set(LAPIS_include_dirs "${CMAKE_CURRENT_LIST_DIR}/Include" 
    CACHE PATH "Path to Lapis headers")

# Create a list of all of the lapis libraries, link all of the 
# lapis libs to lapis core library
set(LAPIS_LIBRARIES lapis_core lapis_window lapis_ui lapis_gfx lapis_alloc lapis)
foreach(lapis_lib ${LAPIS_LIBRARIES})
    add_library(${lapis_lib} "Include/lapis/${lapis_lib}.h")
    meso_apply_target_settings(${lapis_lib})
    target_include_directories(${lapis_lib} PUBLIC 
        "${CMAKE_CURRENT_LIST_DIR}/Include")

    if(NOT ${lapis_lib} STREQUAL "lapis_core")
        target_link_libraries(${lapis_lib} PUBLIC lapis_core)
    endif()
endforeach()

# Link main lapis library to all the sub libraries
foreach(lapis_lib ${LAPIS_LIBRARIES})
    if(NOT ${lapis_lib} STREQUAL "lapis")
        target_link_libraries(lapis PUBLIC ${lapis_lib})
    endif()
endforeach()

# Create the rest of the dependency chain for the lapis libraries 
# i.e UI uses GFX, GFX uses window
target_link_libraries(lapis_gfx PUBLIC lapis_window)
target_link_libraries(lapis_ui PUBLIC lapis_window)
target_link_libraries(lapis_ui PUBLIC lapis_gfx)

# Add all of the source files by going into each directory for each sub component
foreach(lapis_lib ${LAPIS_LIBRARIES})
    if(NOT ${lapis_lib} STREQUAL "lapis")
        string(REPLACE "lapis_" "" lapis_folder ${lapis_lib} )
        add_subdirectory(Source/${lapis_folder})
    endif()
endforeach()

# =================================================================
# Add the Lapis examples
if(${MESO_BUILD_EXAMPLES})
    message(STATUS "Adding Lapis examples")
   add_subdirectory(Examples)
endif()

# =================================================================
# Sort all of the targets
foreach(lapis_lib ${LAPIS_LIBRARIES})
    message(STATUS "Sorting ${lapis_lib}")
    meso_sort_target(${lapis_lib})
endforeach()

