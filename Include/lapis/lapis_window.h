/*************************************************************************************************************
 * Lapis Window
 *
 * Provide the most basic windowing system, and that includes giving all platforms a common entry point
 *
 * License   : GPL3
 * Copyright : 2022 Mesopotamic
 * Authours  : Lawrence G
 *************************************************************************************************************/
#ifndef __LAPIS_WINDOW_HEADER_H__
#define __LAPIS_WINDOW_HEADER_H__ (1)
#include "lapis_core.h"

/**
 * Lapis Window - Supply all of the information needed to allocate and then create a window
 */

// Represents the window
typedef LapisStructure LapisWindow;

// Struct which helps lapis calcualte the size of a window and also how to fill in internal information
typedef struct LapisWindowHelper {
    uint32_t width;
    uint32_t height;
} LapisWindowHelper;

// Fetch the size of the render target
LapisReturnCode lapis_size_window(LapisSize* size, LapisWindowHelper* helper);

/**
 * @breif Creates a lapis window which has been allocated
 * @returns Lapis success code
 * @param context Pointer to the context to create the window with
 * @param window Pointer to the window to create
 * @param helper Pointer to the helper stuct so that lapis knows how to create the window
 */
LapisReturnCode lapis_create_window(LapisContext* context, LapisWindow* window, LapisWindowHelper* helper);

/**
 * Window manipulation functions
 */

/**
 * @brief Poll the window for what events it has recieved
 * @returns Lapis Success Code
 * @param window Pointer to the window to pool events for
 */
LapisReturnCode lapis_window_poll_events(LapisWindow* window);

/**
 * @brief Swaps the onscreen buffer for the offscreen one, this is a thread blocking function until Vsync
 * happens
 * @returns Lapis success code
 * @param window The window to swap inscreen buffers for
 */
LapisReturnCode lapis_window_swap(LapisWindow* window);

/**
 * @brief Checks if the lapis window has recieved a shut down event
 * @returns 0 if the window should stay open, 1 if it should close
 * @param window Pointer to the window to check the status of close
 */
uint8_t lapis_window_stay_open(LapisWindow* window);

#endif  // !__LAPIS_WINDOW_HEADER_H__
