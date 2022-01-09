#include <core/engine.h>
#include <renderer/renderer.h>
#include <cglm/cglm.h>
#include <cglm/struct.h>

texture mario;
texture toad;

void start() {
  mario = texture_create(image_load("../assets/textures/mario.png"));
  mario.width = 128;
  mario.height = 128;

  toad = texture_create(image_load("../assets/textures/toad.png"));
  toad.width = 128;
  toad.height = 128;
}

b8 update(f32 dt) {

}

b8 render(f32 dt) {
  renderer_draw_quad(&mario, (vec2s){64.0f, 64.0f});
  renderer_draw_quad(&toad, (vec2s){96.0f, 64.0f});
}

int main(void) {
  engine_create(640, 480, "vally");
  engine_run(start, update, render);
  return 0;
}
