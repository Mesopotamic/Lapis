#include "wii_gfx.h"

LapisReturnCode lapis_size_target(LapisSize* size, LapisWindowHelper* helper)
{
    return e_lapis_return_success;
}

LapisReturnCode lapis_window_fill_target_helper(LapisWindow* window, LapisTargetHelper* helper) {}

LapisReturnCode lapis_create_gfx_target(LapisTarget* target, LapisTargetHelper* helper)
{
    return e_lapis_return_success;
}

LapisReturnCode lapis_gfx_target_schedule(LapisTarget* target) { return e_lapis_return_success; }

LapisReturnCode lapis_gfx_target_clear(LapisTarget* target, float* color) { return e_lapis_return_success; }
