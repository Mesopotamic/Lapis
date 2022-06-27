/*************************************************************************************************************
 * Lapis
 * Lapis provides a ~hopefully~ cross platform rendering backend for almost any type of 3D accelerated
 * platform. How do we accomplish this? There are two parts, the online and offline parts.
 *
 * Offline :
 * we must optimise the meshes to suit the performance of the backend, the user can specify how much of each
 * resource they want to dedicate to an object, for example in super mario 64, mario takes up half the vertex
 * count in any scene. So users would tag mario with 50% vertex, but much less vram as the level uses a lot
 * more textures, This is how we should make rendering meshes somewhat crossplatform
 *
 * Online :
 * There are a certain number of vertex attributes and others properties that a user might want to request a
 * draw with. For example n64 is only gonna accept vertex pos, uv, and albedo textures.
 * But a wii will also support vertex normals etc.
 * so we inform you which properties a backend supports, from there you can make a draw call by loading in the
 * supported vertex attributes from the processed mesh, that way you don't waste memory, and then any draw
 * calls using ignored properties will be ignored
 *
 * As with most Meso projects, I will try to avoid internal memory allocs and as the user to perform those for
 * us
 * License   : GPL3
 * Copyright : 2022 Mesopotamic
 * Authours  : Lawrence G
 *************************************************************************************************************/
#ifndef __LAPIS_MAIN_HEADER_H__
#define __LAPIS_MAIN_HEADER_H__ (1)
#include <stdint.h>

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
 * LAPIS TYPE DEFINITIONS
 * What:
 *     Lapis types are split into two different parts, the cpu only visible memory and the gpu visible memory.
 *     It is the responsibility of the user to allocate the memory backing these structs. The lapis types are
 *     always typedef'd void pointers, so you can find the size of the structures to allocate
 *     via lapis_TYPENAME_size and lapis_TYPENANE_size_gpu.
 *
 * How:
 *     Allocating a lapis struct will look like this :
 *     LapisContext ctx = {lapis_cpu_alloc(lapis_context_size()), lapis_gpu_alloc(lapis_context_size_gpu())};
 *
 * Why:
 *     1)  It's very normal for games to roll their own memory allocators, so the library should never use
 *     dynamic memory allocation internally, that way it makes it easier to migrate between default allocators
 *     and your own custom ones.
 *     2)  I want to make lapis a drop in solution, exposing the contents of the structs
 *     means that users that add lapis.h into their projects will have to add a bunch of preproccessors
 *     statements and include paths
 *
 * Gpu memory allocation on so many platforms :
 *     Lapis is supposed to be a drop in solution which supports a wide spectrum of different platforms, each
 *     with their own way to allocate memory the gpu can see. It wouldn't be very drag and drop if lapis
 *     expected users to create their own allocators for every single platform. To this end, we have a helper
 *     library which is called lapis_utils, which will provide an abstraction layer for gpu and cpu
 *     allocations.
 *     Then if the user decides the lapis solution isn't good enough, they can make their own allocators and
 *     then the user only has to replace the function calls
 *************************************************************************************************************/

// Represents all the state for the graphics context
typedef struct LapisContext {
    void* cpu_mem;
    void* gpu_mem;
} LapisContext;

size_t lapis_context_size();
size_t lapis_context_size_gpu();

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
