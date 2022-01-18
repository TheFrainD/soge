/*********************************************************************
 * spriterenderer.h                                                  *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_SPRITERENDERER_H_
#define VALLY_SPRITERENDERER_H_

#include <vally/config.h>
#include <vally/renderer/texture.h>
#include <vally/ecs/ecs.h>
#include <vally/math/math.h>

/**
 * @brief Texture coordinates.
 *
 */
typedef struct {
  vector2f uv[4];
} uvs;

/**
 * @brief Sprite atlas struct.
 *
 */
typedef struct {
  vector2f tiling;
  u32 sprite_count;
  u32 sprites_per_row;
  uvs *uvs;
} atlas;

/**
 * @brief Spriterenderer struct.
 *
 */
typedef struct {
  entity entity;
  texture *texture;
  vector2f size;
  uvs uvs;
  atlas atlas;
} spriterenderer;

/**
 * @brief Adds spriterenderer component to entity.
 *
 * @param entity entity
 * @param texture texture of sprite
 *
 */
VALLY_API void ecs_spriterenderer_add(entity entity, texture *texture);

/**
 * @brief Adds spriterenderer component to entity from atlas.
 *
 * Uses sprite atlas to generate sprite.
 *
 * @param entity entity
 * @param texture texture of atlas
 * @param tiling tiling of atlas
 *
 */
VALLY_API void ecs_spriterenderer_add_from_atlas(entity entity, texture *texture, vector2f tiling);

/**
 * @brief Selects certain sprites in sprite atlas.
 *
 * @param enitity entity 
 * @param index index of sprite in atlas
 *
 */
VALLY_API void ecs_spriterenderer_atlas_select(entity entity, u32 index);

/**
 * @brief Gets spriterenderer component instance.
 *
 * @param enitity entity
 * @return Spriterenderer component instance or NULL if entity does not have this component
 *
 */
VALLY_API spriterenderer *ecs_spriterenderer_get(entity entity);

void ecs_spriterenderer_update();

#endif // VALLY_SPRITERENDERER_H_
