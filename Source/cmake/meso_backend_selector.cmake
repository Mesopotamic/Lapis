# Detect which backend should be used from the current build params
# from there we can automatically select the right file path
# Defines
# meso_gfx_backend - glsl, Wiigx etc
# meso_window_backend - win32, wiigx etc
if(WIN32)
	set(meso_gfx_backend "glsl")
	set(meso_window_backend "win32")
endif()