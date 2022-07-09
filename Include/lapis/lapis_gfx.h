/*************************************************************************************************************
 * Lapis - Gfx
 * Graphics content for lapis
 *
 * License   : GPL3
 * Copyright : 2022 Mesopotamic
 * Authors   : Lawrence G
 *************************************************************************************************************/
#ifndef __LAPIS_GRAPHICS_EXTERNAL_HEADER_H__
#define __LAPIS_GRAPHICS_EXTERNAL_HEADER_H__ (1)
#include "lapis_window.h"

/**
 * Lapis Target Supply all of the information needed to allocate and then create the target
 */

// Represents an area that we can render to. One of these is contained in the window, they can be subdivided
typedef LapisStructure LapisTarget;

// Helper to figure help lapis find out how much space to allocate for a target, and how to create it
typedef struct LapisTargetHelper {
    uint32_t width;
    uint32_t height;
} LapisTargetHelper;

// Fetch the size of the lapis render target
LapisReturnCode lapis_size_target(LapisSize* size, LapisWindowHelper* helper);

// Special helper function which will fill in the target helper information from the selected window
LapisReturnCode lapis_window_fill_target_helper(LapisWindow* window, LapisTargetHelper* helper);

/**
 * @brief Creates a lais target to render to
 * @param returns a lapis success code
 * @param window Pointer to a window to own the target, null pointer for offscreen targets
 * @param target Pointer to the target to create
 * @param helper Pointer to the helper struct so that lapis knows how ti create the target
 */
LapisReturnCode lapis_create_gfx_target(LapisTarget* target, LapisTargetHelper* helper);

/**
 * Target manipulation functions
 */

/**
 * @brief Schedules a target as outdated and ready for updating next time a window flips
 * @param returns Lapis siccess code
 * @param target The lapis target to schedule an update for
 */
LapisReturnCode lapis_gfx_target_schedule(LapisTarget* target);

/**
 * @brief Clears the target to the requested color
 * @returns Lapis success code
 * @param target Pointer to the lapis target to clear
 * @param color An array of 3 floats representing the clear color
 */
LapisReturnCode lapis_gfx_target_clear(LapisTarget* target, float* color);

/**
 * Lapis immediate mode graphics functions. This is where triangles are submitted directly as a series of 9
 * floats, thats 3 floats per vertex each with different properties. These are when the information isn't very
 * complex and you don't want to upload the mesh first
 */

/**
 * @breif Immediatley render triangles which have vertex positions and color information
 * @param targget The lapis target to render the triangle list to
 * @param pos An array of vertex positions, in xyz format 3 floats per position
 * @param col An array of colors, in xyz format. 3 floats per color
 * @param tri_count Number of triangles in the list
 */
LapisReturnCode lapis_gfx_immediate_pos_color(LapisTarget* target, float* pos, float* col,
                                              uint32_t tri_count);

#endif
