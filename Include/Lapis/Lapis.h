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
 * Define all of the different structures that lapis uses, they are most likely to take two forms.
 *     1) either a typedef'd void pointer which means either the size changes depending on the built backend,
 *        or it includes a structure from another subproject that we don't see the need to expose to the user.
 *        Along with that typedef, we'll also define an extern const corresponding to the size of the object
 *        in bytes so that users can allocate for memory for them
 *
 *     2) A regular struct - this is going to be less common, as a lot of things change based on the backend.
 *************************************************************************************************************/

// Represents all the state for the graphics context
typedef void* LapisContext;
// How many bytes need to be allocated to a buffer to correctly represent a lapis context
extern const size_t k_lapis_context_size;

#endif  // !__LAPIS_MAIN_HEADER_H__
