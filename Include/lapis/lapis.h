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
 * LAPIS BACKEND FEATURES
 * Define all of the different features a lapis backend might support, since they are consts, at compile or
 * link time then compilers are most likely going to be able to optimise out the unnecacary stuff on backends
 * which support fewer features, which are also more likely to require higher optimisation
 *************************************************************************************************************/

// Features that tell the user which features the backend supports which effects how the user will want to
// load meshes. For example if the backend does not support normal maps, then there's no need to load them
// from the disk, and if you are using a lapis processed mesh, then the mesh won't even have the features not
// supported by the backend
typedef enum LapisMeshFeatureFlags {
    e_lapis_feature_vertex_pos = 0x1 << 0,      // Supports vertex positions, all backends should support this
    e_lapis_feature_index_buffer = 0x1 << 1,    // Supports subitting geometry along with an index buffer
    e_lapis_feature_vertex_color = 0x1 << 2,    // Supports colours sent per vertex
    e_lapis_feature_vertex_norm = 0x1 << 3,     // Supports normals vectors sent per vertex
    e_lapis_feature_vertex_tangent = 0x1 << 4,  // Supports tangent vectors sent per vertex
    e_lapis_feature_vertex_tex_uv = 0x1 << 5,   // Supports texture coordinates, needed for any textures
    e_lapis_feature_texture_albedo = 0x1 << 6,  // Supports albedo textures
    e_lapis_feature_texture_normal = 0x1 << 7,  // Supports normal map textures
} LapisMeshFeatureFlags;

// The mesh features supported by the backend lapis was built for
extern const LapisMeshFeatureFlags k_lapis_mesh_feature_mask;

// Features that tell the user which type of effects can be applied to a draw, it does not effect asset
// loading, but it's always helpfull to know if your backend has dynamic shadows etc
typedef enum LapisDrawFeatureFlags {
    e_lapis_feature_draw_dynamic_shadows = 0x1 << 0,  // Shadows can be caluclated at runtime from lights
} LapisDrawFeatureFlags;

// The extra drawing features that can be applied to individual draw calls based on the backend lapis was
// built for
extern const LapisDrawFeatureFlags k_lapis_draw_feature_mask;

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
