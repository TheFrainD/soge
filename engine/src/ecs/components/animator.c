#include "ecs/components/animator.h"

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

  state.components[entity] = (animator){NULL, 0, 0.0f};
  ecs_component_add(entity, ECS_ANIMATOR_COMPONENT);
}

void ecs_animator_play(entity entity, animation *animation) {
  if (entity == ECS_NULL_ENTITY || !ecs_component_has(entity, ECS_ANIMATOR_COMPONENT | ECS_SPRITERENDERER_COMPONENT)) {
    return;
  }

  state.components[entity].animation = animation;
  state.components[entity].current_frame = animation->first_frame;
  state.components[entity].time = 0.0f;

  ecs_spriterenderer_add_from_atlas(entity, animation->texture, animation->tiling);
  ecs_spriterenderer_atlas_select(entity, animation->first_frame);
}

void ecs_animator_stop(entity entity) {
  if (entity == ECS_NULL_ENTITY || !ecs_component_has(entity, ECS_ANIMATOR_COMPONENT | ECS_SPRITERENDERER_COMPONENT)) {
    return;
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