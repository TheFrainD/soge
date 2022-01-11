#ifndef VALLY_ECS_COMPONENTS_SPRITERENDERER_H_
#define VALLY_ECS_COMPONENTS_SPRITERENDERER_H_

#include <vally/config.h>
#include <vally/renderer/texture.h>
#include <vally/ecs/ecs.h>
#include <vally/math/math.h>

typedef struct {
  vector2f uv[4];
} uvs;

typedef struct {
  vector2f tiling;
  u32 sprite_count;
  u32 sprites_per_row;
  uvs *uvs;
} atlas;

typedef struct {
  entity entity;
  texture *texture;
  vector2f size;
  uvs uvs;
  atlas atlas;
} spriterenderer;

VALLY_API void ecs_spriterenderer_add(entity entity, texture *texture);

VALLY_API void ecs_spriterenderer_add_from_atlas(entity entity, texture *texture, vector2f tiling);

VALLY_API void ecs_spriterenderer_atlas_select(entity entity, u32 index);

VALLY_API spriterenderer *ecs_spriterenderer_get(entity entity);

void ecs_spriterenderer_update();

#endif // !VALLY_ECS_COMPONENTS_SPRITERENDERER_H_