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

#endif  // !__LAPIS_MAIN_HEADER_H__
