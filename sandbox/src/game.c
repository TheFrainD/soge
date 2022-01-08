#include <core/engine.h>
#include <renderer/renderer.h>
#include <cglm/cglm.h>
#include <cglm/struct.h>

texture mario;

void start() {
  mario = texture_create(load_image("../assets/textures/mario.png"));
}

b8 update(f32 dt) {

}

b8 render(f32 dt) {
  renderer_draw_quad(&mario, (vec2s){64.0f, 64.0f});
}

int main(void) {
  engine_create(640, 480, "vally");
  engine_run(start, update, render);
  return 0;
}
