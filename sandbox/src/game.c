#include <core/engine.h>

void start() {
  
}

b8 update(f32 dt) {

}

b8 render(f32 dt) {

}

int main(void) {
  engine_create(640, 480, "vally");
  engine_run(start, update, render);
  return 0;
}