#ifndef VALLY_RENDERER_CAMERA_H_
#define VALLY_RENDERER_CAMERA_H_

#include "defines.h"

#include <cglm/cglm.h>
#include <cglm/struct.h>

typedef struct {
  mat4s projection;
  mat4s view;
  vec2s position;
} camera;

b8 camera_init();
mat4s camera_update_projection(i32 width, i32 height);
mat4s camera_update_view();
mat4s camera_get_projection();
mat4s camera_get_view();
void camera_translate(vec2s translation);

#endif // !VALLY_RENDERER_CAMERA_H_