#ifndef VALLY_ECS_COMPONENTS_ANIMATOR_H_
#define VALLY_ECS_COMPONENTS_ANIMATOR_H_

#include <vally/config.h>

#include <vally/renderer/texture.h>
#include <vally/ecs/ecs.h>

typedef struct {
  texture *texture;
  vector2f tiling;
  u32 first_frame;
  u32 last_frame;
  f32 frametime;
} animation;

typedef struct {
  b8 playing;
  animation *animation;
  u32 current_frame;
  f32 time;
} animator;

VALLY_API animation animation_create(texture *texture, vector2f tiling, u32 first_frame, u32 last_frame, u32 framerate);

VALLY_API void ecs_animator_add(entity entity);

VALLY_API void ecs_animator_play(entity entity, animation *animation);

VALLY_API void ecs_animator_stop(entity entity);

void ecs_animator_update(f32 dt);

#endif // !VALLY_ECS_COMPONENTS_ANIMATOR_H_