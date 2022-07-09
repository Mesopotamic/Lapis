/*************************************************************************************************************
 * Lapis - Alloc
 * One of the helper libraries which users can implement themselves if required
 *
 * License   : GPL3
 * Copyright : 2022 Mesopotamic
 * Authors   : Lawrence G
 *************************************************************************************************************/
#ifndef __LAPIS_ALLOC_EXTERNAL_HEADER_H__
#include "lapis_core.h"

/**
 * @brief Allocates a lapis structure for the user
 * @returns Lapis success code
 * @param object Pointer to the object to be allocated
 * @param type enum for the type of object to be allocated for
 */
LapisReturnCode lapis_allocate(LapisStructure* object, LapisType type);

/**
 * @brief Allocates a lapis structure for the user when the structure's size depends on it's properties
 * @returns Lapis success code
 * @param object Pointer to the object to be allocated
 * @param helper pointer to the struct containing helper information
 * @param type enum for the type of object to be allocated for
 */
LapisReturnCode lapis_allocate_dynamic(LapisStructure* object, void* helper, LapisType type);

/**
 * @brief Free a lapis structure which has been allocated with lapis_alloc
 * @returns Lapis success code
 * @param object the lapis object to free
 */
LapisReturnCode lapis_free(LapisStructure* object);

#endif
