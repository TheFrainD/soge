#include "ecs/components/spriterenderer.h"

#include <stdlib.h>

#include "core/logger.h"
#include "renderer/renderer.h"

typedef struct {
  spriterenderer components[ECS_MAX_COMPONENTS];
} spriterenderer_state;

static spriterenderer_state state;

void ecs_spriterenderer_add(entity entity, texture *texture) {
  if (entity == ECS_NULL_ENTITY) {
    return;
  }

  spriterenderer component;
  component.entity = entity;
  component.texture = texture;
  component.size = vector2f_create(texture->width, texture->height);

  component.uvs.uv[0] = vector2f_create(0.0f, 0.0f);
  component.uvs.uv[1] = vector2f_create(1.0f, 0.0f);
  component.uvs.uv[2] = vector2f_create(1.0f, 1.0f);
  component.uvs.uv[3] = vector2f_create(0.0f, 1.0f);

  component.atlas = (atlas){component.size, 1, 1, NULL};

  state.components[entity] = component;
  ecs_component_add(entity, ECS_SPRITERENDERER_COMPONENT);
}

void ecs_spriterenderer_add_from_atlas(entity entity, texture *texture, vector2f tiling) {
  if (entity == ECS_NULL_ENTITY) {
    return;
  }

  spriterenderer component;
  component.entity = entity;
  component.texture = texture;
  component.size = tiling;

  atlas atlas;
  atlas.tiling = tiling;
  atlas.sprites_per_row = texture->width / tiling.x;
  atlas.sprite_count = atlas.sprites_per_row * (texture->height / tiling.y);
  atlas.uvs = (uvs *)malloc(sizeof(uvs) * atlas.sprite_count);
  for (i32 i = 0; i < atlas.sprite_count; i++) {
    f32 tw = tiling.x / texture->width;
    f32 th = tiling.y / texture->height;
    f32 tx = (i % atlas.sprites_per_row) * tw;
    f32 ty = (i / atlas.sprites_per_row) * th;

    atlas.uvs[i].uv[0] = vector2f_create(tx, ty);
    atlas.uvs[i].uv[1] = vector2f_create(tx + tw, ty);
    atlas.uvs[i].uv[2] = vector2f_create(tx + tw, ty + th);
    atlas.uvs[i].uv[3] = vector2f_create(tx, ty + th);
  }

  component.atlas = atlas;
  component.uvs = atlas.uvs[0];

  state.components[entity] = component;
  ecs_component_add(entity, ECS_SPRITERENDERER_COMPONENT);
}

void ecs_spriterenderer_atlas_select(entity entity, u32 index) {
  if (entity == ECS_NULL_ENTITY || !ecs_component_has(entity, ECS_SPRITERENDERER_COMPONENT)) {
    return;
  }

  spriterenderer *spriterenderer = &state.components[entity];
  spriterenderer->uvs = spriterenderer->atlas.uvs[index];
}

spriterenderer *ecs_spriterenderer_get(entity entity) {
  if (entity == ECS_NULL_ENTITY || !ecs_component_has(entity, ECS_SPRITERENDERER_COMPONENT)) {
    return NULL;
  }

  return &state.components[entity];
}

void ecs_spriterenderer_update() {
  for (entity e = 0; e < ecs_get_last(); e++) {
    if (ecs_is_alive(e) && ecs_component_has(e, ECS_SPRITERENDERER_COMPONENT)) {
      renderer_draw(&state.components[e]);
    }
  }
}