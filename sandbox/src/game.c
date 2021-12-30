#include <core/engine.h>

int main(void) {
  engine_create(640, 480, "Test");
  engine_run();
  return 0;
}