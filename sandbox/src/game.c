#include <core/engine.h>
#include <core/input.h>
#include <renderer/renderer.h>
#include <cglm/cglm.h>
#include <cglm/struct.h>

texture mario;
texture toad;

vec2s mario_pos = GLMS_VEC2_ZERO;
f32 speed = 100;

void start() {
  mario = texture_create(image_load("../assets/textures/mario.png"));
  mario.width = 128;
  mario.height = 128;

  toad = texture_create(image_load("../assets/textures/toad.png"));
  toad.width = 128;
  toad.height = 128;
}

b8 update(f32 dt) {
  if (input_key_pressed(KEY_W)) {
    mario_pos.y -= speed * dt;
  } else if (input_key_pressed(KEY_S)) {
    mario_pos.y += speed * dt;
  }

  if (input_key_pressed(KEY_A)) {
    mario_pos.x -= speed * dt;
  } else if (input_key_pressed(KEY_D)) {
    mario_pos.x += speed * dt;
  }
}

b8 render(f32 dt) {
  renderer_draw_quad(&mario, mario_pos);
  renderer_draw_quad(&toad, (vec2s){96.0f, 64.0f});
}

int main(void) {
  engine_create(640, 480, "vally");
  engine_run(start, update, render);
  return 0;
}
