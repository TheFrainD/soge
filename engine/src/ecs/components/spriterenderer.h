#ifndef VALLY_ECS_COMPONENTS_SPRITERENDERER_H_
#define VALLY_ECS_COMPONENTS_SPRITERENDERER_H_

#include "defines.h"
#include "renderer/texture.h"
#include "ecs/ecs.h"
#include "math/vmath.h"

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

VALLY_DLL void ecs_spriterenderer_add(entity entity, texture *texture);

VALLY_DLL void ecs_spriterenderer_add_from_atlas(entity entity, texture *texture, vector2f tiling);

VALLY_DLL void ecs_spriterenderer_atlas_select(entity entity, u32 index);

VALLY_DLL spriterenderer *ecs_spriterenderer_get(entity entity);

void ecs_spriterenderer_update();

#endif // !VALLY_ECS_COMPONENTS_SPRITERENDERER_H_