# Creates a cross-platform cmake executable which can be used to have a crossplatform executable with common entry point

function(meso_add_executable target_name)

	# We can set cmake linker flags before creating the executable, and they 
	# will be caried on to the executable. For example on windows we can set
	# the entry point so that int main can be used without spawning a terminal
	if(WIN32)
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} 
			/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") 
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