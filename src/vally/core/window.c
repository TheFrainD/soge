/*********************************************************************
 * window.c                                                          *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#include <vally/core/window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vally/core/logger.h>
#include <vally/core/event.h>

typedef struct {
  GLFWwindow *window;
  i32 width;
  i32 height;
  char *title;
} window_state;

static b8 initialized = FALSE;
static window_state state;

static void window_size_callback(GLFWwindow *window, i32 width, i32 height) {
  state.width = width;
  state.height = height;
  glViewport(0, 0, width, height);
  event_context context;
  context.data.f32[0] = (float)width;
  context.data.f32[1] = (float)height;
  event_publish(EVENT_CODE_WINDOW_RESIZED, &state, context);
}

static void window_error_callback(i32 id, const char *description) {
  LOG_ERROR("GLFW error: %s", description);
}


b8 window_create(i32 width, i32 height, char* title) {
  if (initialized) {
    return FALSE;
  }
  state.width = width;
  state.height = height;
  state.title = title;

  glfwSetErrorCallback(window_error_callback);
  if (!glfwInit()) {
    LOG_FATAL("Could not initialize GLFW!");
    return FALSE;
  }
  LOG_TRACE("GLFW initialized");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  state.window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!state.window) {
    LOG_FATAL("Could not create window!");
    return FALSE;
  }
  LOG_TRACE("Window created");
  glfwMakeContextCurrent(state.window);
  glfwSwapInterval(1);

  glfwSetWindowSizeCallback(state.window, window_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    LOG_FATAL("Could not initialize glad!");
    return FALSE;
  }
  LOG_TRACE("glad initialized");

  glViewport(0, 0, width, height);

  LOG_INFO("System Info:");
  LOG_INFO("Vendor: %s", glGetString(GL_VENDOR));
  LOG_INFO("Renderer: %s,", glGetString(GL_RENDERER));
  i32 major, minor;
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  glGetIntegerv(GL_MINOR_VERSION, &minor);
  LOG_INFO("OpenGL version: %d.%d", major, minor);

  return TRUE;
}

b8 window_poll_events() {
  glfwPollEvents();
  return !glfwWindowShouldClose(state.window);
}

void window_swap_buffers() {
  glfwSwapBuffers(state.window);
}

void window_terminate() {
  glfwDestroyWindow(state.window);
  glfwTerminate();
  LOG_TRACE("Window subsystem terminated");
}

void window_set_key_callback(void *callback) {
  glfwSetKeyCallback(state.window, callback);
}

void window_set_mouse_button_callback(void *callback) {
  glfwSetMouseButtonCallback(state.window, callback);
}

void window_set_cursor_position_callback(void *callback) {
  glfwSetCursorPosCallback(state.window, callback);
}

i32 window_get_width() {
  return state.width;
}

i32 window_get_height() {
  return state.height;
}
