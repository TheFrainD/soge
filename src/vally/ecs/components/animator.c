/*********************************************************************
 * animator.c                                                        *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#include <vally/ecs/components/animator.h>

#include <stddef.h>

typedef struct {
  animator components[ECS_MAX_COMPONENTS];
} animator_state;

static animator_state state;

animation animation_create(texture *texture, vector2f tiling, u32 first_frame, u32 last_frame, u32 framerate) {
  return (animation){texture, tiling, first_frame, last_frame, 1.0f / framerate};
}

void ecs_animator_add(entity entity) {
  if (entity == ECS_NULL_ENTITY) {
    return;
  }

  state.components[entity] = (animator){FALSE, NULL, 0, 0.0f};
  ecs_component_add(entity, ECS_ANIMATOR_COMPONENT);
}

void ecs_animator_play(entity entity, animation *animation) {
  if (entity == ECS_NULL_ENTITY || !ecs_component_has(entity, ECS_ANIMATOR_COMPONENT | ECS_SPRITERENDERER_COMPONENT)) {
    return;
  }

  if (!(state.components[entity].playing && state.components[entity].animation == animation)) {
    state.components[entity].playing = TRUE;
    state.components[entity].animation = animation;
    state.components[entity].current_frame = animation->first_frame;
    state.components[entity].time = 0.0f;

    ecs_spriterenderer_add_from_atlas(entity, animation->texture, animation->tiling);
    ecs_spriterenderer_atlas_select(entity, animation->first_frame);
  }
}

void ecs_animator_stop(entity entity) {
  if (entity == ECS_NULL_ENTITY || !ecs_component_has(entity, ECS_ANIMATOR_COMPONENT | ECS_SPRITERENDERER_COMPONENT)) {
    return;
  }

  state.components[entity].playing = FALSE;
  if (state.components[entity].animation != NULL) {
    ecs_spriterenderer_atlas_select(entity, state.components[entity].animation->first_frame);
  }
  state.components[entity].animation = NULL;
}

void ecs_animator_update(f32 dt) {
  for (entity e = 0; e < ecs_get_last(); e++) {
    if (ecs_is_alive(e) && ecs_component_has(e, ECS_ANIMATOR_COMPONENT | ECS_SPRITERENDERER_COMPONENT)) {
      animator *animator = &state.components[e];
      animation *animation = animator->animation;
      if (animator->animation != NULL) {
        animator->time += dt;
        if (animator->time >= animation->frametime) {
          animator->time = 0.0f;
          ecs_spriterenderer_atlas_select(e, animator->current_frame++);
          if (animator->current_frame > animation->last_frame) {
            animator->current_frame = animation->first_frame;
          }
        }
      }
    }
  }
}