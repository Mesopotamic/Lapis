/*************************************************************************************************************
 * Lapis - Core
 * Provides the base Lapis library, common enums and type declarations along with the functions which tell you
 * how large the types are. Included into every other lapis project
 *
 * License   : GPL3
 * Copyright : 2022 Mesopotamic
 * Authours  : Lawrence G
 *************************************************************************************************************/
#ifndef __LAPIS_CORE_EXTERNAL_HEADER_H__
#define __LAPIS_CORE_EXTERNAL_HEADER_H__ (1)
#include <stdint.h>

/*************************************************************************************************************
 * LAPIS TYPE DEFINITIONS
 * What:
 *     Lapis types are split into two different parts, the cpu only visible memory and the gpu visible memory.
 *     It is the responsibility of the user to allocate the memory backing these structs. The lapis types are
 *     always typedef'd void pointers, you can use lapis_get_size(&size, TYPE) to get size and allignment
 *     required for the struct to be allocated correctly.
 *
 * How:
 *     Allocating a lapis struct can look like this, common cpu allocator would be malloc, and the gpu
 *     allocator function would likely change per platform
 *         LapisSize size;
 *         lapis_get_size(&size, e_lapis_type_context);
 *         LapisContext ctx = {
 *                             cpu_allocate(size.cpu_size),
 *                             gpu_allocate(size.gpu_size, size.gpu_allignment)
 *                            };
 *
 *     However if you are using the allocators inside of lapis_alloc for a simpler experience
 *         LapisContext ctx;
 *         lapis_alloc(&ctx, e_lapis_type_context);
 *
 * Why:
 *     1)  It's very normal for games to roll their own memory allocators, so the library should never use
 *     dynamic memory allocation internally, that way users can easily use their own allocators, or rely
 *     on the built in ones if they are fast enough. The main point is that migrating between the two
 *     wouldn't involve rebuilding the lapis libraries
 *
 *     2)  I want to make lapis a drop in solution, exposing the contents of the structs
 *     means that users which add lapis.h into their projects will be forced to add a bunch of preproccessors
 *     statements and include paths. I want users to just be able to use lapis.h as is.
 *************************************************************************************************************/
typedef enum LapisType {
    e_lapis_type_context,  // The context that holds everything to get started
} LapisType;

// Represents the information required to represent a gpu memory allocation. We're using size_t as it should
// be able to hold any size which can be addressed because malloc uses size_t. However, maybe this should
// change to uintptr_t? But I don't know if this strictly appeals to C90 standard
typedef struct LapisSize {
    size_t cpu_size;
    size_t gpu_size;
    uint32_t gpu_align;
} LapisSize;

// Represents all the state for the graphics context
typedef struct LapisContext {
    void* cpu_mem;
    void* gpu_mem;
} LapisContext;

#endif
