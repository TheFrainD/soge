#include <core/engine.h>
#include <core/input.h>
#include <ecs/ecs.h>
#include <ecs/components/spriterenderer.h>
#include <ecs/components/transform.h>
#include <math/vmath.h>

entity mario;
entity toad;
entity stone;

texture *terrain;
animation anim;

void start() {
  mario = ecs_entity_create();
  ecs_spriterenderer_add(mario, texture_create(image_load("../assets/textures/mario.png")));
  ecs_transform_get(mario)->scale = vector2f_create(0.25f, 0.25f);

  toad = ecs_entity_create();
  ecs_spriterenderer_add(toad, texture_create(image_load("../assets/textures/toad.png")));
  ecs_transform_get(toad)->scale = vector2f_create(0.1f, 0.1f);

  terrain = texture_create(image_load("../assets/textures/terrain.png"));
  anim = animation_create(terrain, vector2f_create(16.0f, 16.0f), 0, 4, 1);

  stone = ecs_entity_create();
  ecs_spriterenderer_add_from_atlas(stone, terrain, vector2f_create(16.0f, 16.0f));
  ecs_animator_add(stone);
  ecs_animator_play(stone, &anim);
  //ecs_spriterenderer_atlas_select(stone, 4);
  ecs_transform_get(stone)->scale = vector2f_create(8.0f, 8.0f);
  ecs_transform_get(stone)->position = vector2f_create(64.0f, 64.0f);
}

b8 update(f32 dt) {
  ecs_transform_get(mario)->position.x += 20.0f * dt;
}

b8 render(f32 dt) {

}

int main(void) {
  engine_create(640, 480, "vally");
  engine_run(start, update, render);
  return 0;
}
