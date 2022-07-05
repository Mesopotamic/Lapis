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
 *   |     |     |- Lapis gfx : Provides graphics support
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

// The core library that is included into every other lapis library
#include "lapis_core.h"

// Defines how lapis controlls the windowing loop and user inputs
#include "lapis_window.h"

// Sits on top of window to provide graphics
#include "lapis_gfx.h"

// Sits on top of the graphics library to produce a simplified UI creation
#include "lapis_ui.h"

// Provides the user with some example cross platform memory allocators
#include "lapis_alloc.h"

#endif  // !__LAPIS_MAIN_HEADER_H__
