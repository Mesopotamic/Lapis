/*************************************************************************************************************
 * Lapis
 * This library is designed to be a ~totally~ cross-platform graphics solution - by being written from scratch
 * to C89 standard. We provide different layers of abstracting for multiple different usages, all packed into
 * lapis header. However you should be able to use each of the parts seperatley
 *
 * Most importantly all of the libraries should not use internal dynamic memory allocation so that users can
 * make their own memory allocators and work immediatley with lapis, Specifically this is most likely to be
 * the case in game engines targetting consoles which share memory with the GPU.
 *
 * Lapis components :
 *   |-  Lapis Core : Provides common code and type declarations for runtime applications
 *   |     |-  Lapis Window : Provides basic windowing for users using their own backends
 *   |     |     |- Lapis UI  : Provides UI abstraction like font and button rendering
 *   |     |     |- Lapis gfx : Provides 2d graphics support
 *   |     |-  Lapis Alloc  : Provides example allocators for each of the different backends
 *   |     |                : This is a rare exception as it is allowed to dynamically allocate
 *   |     |                : memory because it is aimed at users who don't want to build their
 *   |     |                : own allocators or manage all the different allocators for all the
 *   |     |                : different platforms
 *   |
 *   |-  Lapis Offline : Provides offline tools to make things nicer for the targeted backend
 *         |-  Lapis Mesh : Provides mesh optimisation for the different backends
 *
 * License   : GPL3
 * Copyright : 2022 Mesopotamic
 * Authours  : Lawrence G
 *************************************************************************************************************/
#ifndef __LAPIS_MAIN_HEADER_H__
#define __LAPIS_MAIN_HEADER_H__ (1)
#include "lapis_core.h"
#include "lapis_ui.h"

/*************************************************************************************************************
 * LAPIS ERROR CODES
 * Most lapis functions are going to want to comunicate with you if they were successful, it's obviously not
 * strictly required that you always check these error codes as a lot of the time they're going to be
 * successful.
 * For example it makes no sense to check every single triangle that you draw is succesful, but maybe if
 * you're having a draw go wrong, you can check the return codes. You're also probably going to want to make
 * sure that you check the return code of the context creation
 *************************************************************************************************************/

typedef enum LapisReturnCode {
    e_lapis_return_success,  // Everything went as expected!
} LapisReturnCode;

/*************************************************************************************************************
 * LAPIS FUNCTION DECLARATIONS
 * Finally with all the preamble out the way we can get onto the most important stuff, the actual library
 * function calls. In order to make functions quicker to find via intellisense, functions follow a hierachical
 * naming scheme. So they all start with "lapis_" followed by the domain in which work is being done, for
 * example "context_" or "draw", followed by what is being done, and finally followed by any extra qualifiers.
 *************************************************************************************************************/

/**
 * @brief Starts the Lapis connection, should be the first lapis call made. For example it will fetch the
 * framebuffer sizes so that we can calculate how much gpu visible memory is required for the user to allocate
 * for the context
 * @returns Lapis success code
 */
LapisReturnCode lapis_connect();

/**
 * @brief Tells the user how much memory they should allocate for a lapis structure.
 * @returns Lapis success code.
 * @param size A pointer to a lapis size align object which will contain the information needed to allocate
 * for the given structure.
 * @param type The lapis type to allocate for.
 */
LapisReturnCode lapis_get_size(LapisSize* size, LapisType type);

/**
 * @breif Takes a lapis context which has already had memory allocated for it, and then produces all of the
 * state needed to be able to start submitting draw calls to the screen. On consoles, width and height are
 * most likely going to be ignored
 * @returns Lapis success code, most likely success.
 * @param context Pointer to the lapis context to be initialised
 * @param width window width
 * @param height window height
 */
LapisReturnCode lapis_context_init(LapisContext* context, uint32_t width, uint32_t height);

/**
 * @breif Takes a lapis context which has already had memory allocated for it, and then produces all of the
 * state needed to be able to start submitting draw calls to the screen. The window is made full screen on the
 * currently operating window
 * @returns Lapis success code, most likely success.
 * @param context Pointer to the lapis context to be initialised
 */
LapisReturnCode lapis_context_init_fullscreen(LapisContext* context);

#endif  // !__LAPIS_MAIN_HEADER_H__
