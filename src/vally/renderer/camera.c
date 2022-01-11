#include <vally/renderer/camera.h>

#include <vally/core/event.h>

typedef struct {
  mat4s projection;
  mat4s view;
  vec2s position;
} camera_state;

static b8 initialized = FALSE;
static camera_state state;

b8 camera_init() {
  if (initialized) {
    return FALSE;
  }
  state.position = GLMS_VEC2_ZERO;
  initialized = TRUE;

  return TRUE;
}

mat4s camera_update_projection(i32 width, i32 height) {
  if (!initialized) {
    return GLMS_MAT4_ZERO;
  }

  state.projection = glms_ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 100.0f);
  return state.projection;
}

mat4s camera_update_view() {
  if (!initialized) {
    return GLMS_MAT4_ZERO;
  }

  vec3s front = {0.0f, 0.0f, -1.0f};
  vec3s up = {0.0f, 1.0f, 0.0f};
  state.view = glms_lookat((vec3s){state.position.x, state.position.y, 20.0f},
    glms_vec3_add(front, (vec3s){state.position.x, state.position.y, 0.0f}), up);
  return state.view;
}

mat4s camera_get_projection() {
  if (!initialized) {
    return GLMS_MAT4_ZERO;
  }
  return state.projection;
}

mat4s camera_get_view() {
  if (!initialized) {
    return GLMS_MAT4_ZERO;
  }
  return state.view;
}

void camera_translate(vec2s translation) {
  if (!initialized) {
    return;
  }

  state.position = glms_vec2_add(state.position, translation);
  event_context context;
  context.data.f32[0] = state.position.x;
  context.data.f32[1] = state.position.y;
  event_publish(EVENT_CODE_CAMERA_MOVED, &state, context);
}