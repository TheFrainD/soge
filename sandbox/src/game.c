#include <core/engine.h>
#include <core/input.h>
#include <ecs/ecs.h>
#include <math/vmath.h>
#include <renderer/camera.h>

entity knight;
animation run_right;
animation run_left;

entity stones[16];

f32 speed = 120.0f;

void start() {
  run_right = animation_create(texture_create(image_load("../assets/textures/knight_right.png")), 
  vector2f_create(16.0f, 16.0f), 0, 5, 12);

  run_left = animation_create(texture_create(image_load("../assets/textures/knight_left.png")), 
  vector2f_create(16.0f, 16.0f), 0, 5, 12);

  texture *terrain = texture_create(image_load("../assets/textures/terrain.png"));
  for (i32 i = 0; i < 16; i++) {
    stones[i] = ecs_entity_create();
    ecs_spriterenderer_add_from_atlas(stones[i], terrain, vector2f_create(16.0f, 16.0f));
    ecs_spriterenderer_atlas_select(stones[i], 1);
    ecs_transform_get(stones[i])->scale = vector2f_create(4.0f, 4.0f);
    ecs_transform_get(stones[i])->position = vector2f_create(0.0f + 64.0f * i, 180.0f);
  }

  knight = ecs_entity_create();
  ecs_spriterenderer_add_from_atlas(knight, texture_create(image_load("../assets/textures/knight_right.png")), vector2f_create(16.0f, 16.0f));
  ecs_animator_add(knight);
  ecs_transform_get(knight)->position = vector2f_create(640.0f / 2.0f - 32.0f, 126.0f);
  ecs_transform_get(knight)->scale = vector2f_create(4.0f, 4.0f);
}

b8 update(f32 dt) {
  f32 translation = 0.0f;

  if (input_key_pressed(KEY_A)) {
    translation = -speed * dt;
    ecs_animator_play(knight, &run_left);
  } else if (input_key_pressed(KEY_D)) {
    translation = speed * dt;
    ecs_animator_play(knight, &run_right);
  } else {
    ecs_animator_stop(knight);
  }

  ecs_transform_get(knight)->position.x += translation;
  if (translation != 0.0f) {
    camera_translate((vec2s){translation, 0.0f});
  }
}

b8 render(f32 dt) {

}

int main(void) {
  engine_create(640, 480, "vally");
  engine_run(start, update, render);
  return 0;
}
