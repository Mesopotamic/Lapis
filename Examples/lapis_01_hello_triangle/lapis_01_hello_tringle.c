#include "lapis/lapis.h"

int main()
{
    // Start lapis
    lapis_connect();

    // Allocate enough space for the lapis context, the user can do this manually
    LapisContext context;
    lapis_allocate(&context, e_lapis_type_context);
    lapis_create_context(&context);

    // Using the context now create a window. Since the window size is going to effect how much memory we need
    // to allocate, we need to tell the window how large we expect it to be. The other important information
    // is that this is only a hint on the requested size. The size might actually be fixed by output screen
    // resolution
    LapisWindow window;
    LapisWindowHelper window_helper;
    window_helper.width = 720;
    window_helper.height = 360;
    lapis_allocate_dynamic(&window, &window_helper, e_lapis_type_window);
    lapis_create_window(&context, &window, &window_helper);

    // We perform all rendering to a target. And although we have a window, we don't have a target, so we need
    // to make an area to render to from the window
    LapisTarget target;
    LapisTargetHelper target_helper;
    lapis_window_fill_target_helper(&window, &target_helper);
    lapis_allocate_dynamic(&target, &target_helper, e_lapis_type_target);
    lapis_create_gfx_target(&target, &target_helper);

    // define the triangle positions in screenspace with 0,0 in the centre with width and height 1. Also
    // supply a list of colours to associate with each vertex will be, this will then be interpolated on the
    // gpu
    float vertex_positions[9] = {// Top
                                 0.0, 0.0, 0.0,
                                 // Right
                                 0.0, 0.0, 0.0,
                                 // Left
                                 0.0, 0.0, 0.0};

    float vertex_colors[9] = {// Top
                              0.0, 1.0, 0.0,
                              // Right
                              0.0, 0.0, 1.0,
                              // Left
                              1.0, 0.0, 0.0};

    // Color to clear the target to every frame
    float clear_color[3] = {0.0, 0.0, 0.0};

    // Enter into the windowing loop every frame, we need to check every frame which events have been
    // performed, and if a shut down event is over then we exit out
    while (lapis_window_stay_open(&window)) {
        lapis_window_poll_events(&window);

        // Every frame request a clear of the target
        lapis_gfx_target_clear(&target, clear_color);

        // Submit the draw as an immediate render directly to the gpu
        lapis_gfx_immediate_pos_color(&target, vertex_positions, vertex_colors, 1);

        // Lapis isn't an immidate mode renderer, as such render targets aren't going to flip manually when
        // VSync comes, Take text rendering for example in a text editor, it doesn't want to render every
        // letter every frame, it just wants to render the one new letter when it's typed
        lapis_gfx_target_schedule(&target);

        // Swap the render targets, this is a thread blocking function until VSync
        lapis_window_swap(&window);
    }

    // Now be good and free the memory we allocated
    lapis_free(&target);
    lapis_free(&window);
}
