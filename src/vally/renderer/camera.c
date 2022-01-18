/*********************************************************************
 * camera.c                                                          *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#include <vally/renderer/camera.h>
#include <vally/renderer/projection.h>

#include <cglm/cglm.h>
#include <cglm/struct.h>

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

  vec3s front = ((vec3s){0.0f, 0.0f, -1.0f});
  vec3s up = ((vec3s){0.0f, 1.0f, 0.0f});
  state.view = glms_lookat(((vec3s){state.position.x, state.position.y, 20.0f}),
    glms_vec3_add(front, ((vec3s){state.position.x, state.position.y, 0.0f})), up);
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

void camera_translate(vector2f translation) {
  if (!initialized) {
    return;
  }

  state.position = glms_vec2_add(state.position, (vec2s){translation.x, translation.y});
  event_context context;
  context.data.f32[0] = state.position.x;
  context.data.f32[1] = state.position.y;
  event_publish(EVENT_CODE_CAMERA_MOVED, &state, context);
}