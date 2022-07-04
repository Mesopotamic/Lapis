# Creates a cross-platform cmake executable which can be used to have a crossplatform executable with common entry point

function(meso_add_executable target_name)

	# Depending on the target platform there may need to be a cmake semantic
	# I.e specifying win32 will change the linker flags to make winmain the entry
	# point and therefore we won't auto spawn a terminal
	if(WIN32)
		set(CMAKE_EXE_SEMANTIC "WIN32")
	else()
		set(CMAKE_EXE_SEMANTIC "")
	endif()

	# If the user has specified source files then they will be in the extra 
	# cmake arguments stored in argn
	add_executable(${target_name} ${CMAKE_EXE_SEMANTIC} ${ARGN})

	# If there is no argn value, then there's no source files
	# set the linker lanuage to let cmake continue on 
	if(NOT ARGN)
		set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE "C") 
	endif()

endfunction()