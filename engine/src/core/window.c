#include <core/window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <core/logger.h>

static GLFWwindow *window;

b8 window_create(i32 width, i32 height, const char* title) {
  if (!glfwInit()) {
    VALLY_FATAL("Could not initialize GLFW!");
    return FALSE;
  }
  VALLY_TRACE("GLFW initialized");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    VALLY_FATAL("Could not create window!");
    return FALSE;
  }
  VALLY_TRACE("Window created");
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    VALLY_FATAL("Could not initialize glad!");
    return FALSE;
  }
  VALLY_TRACE("glad initialized");

  glViewport(0, 0, width, height);

  return TRUE;
}

b8 window_poll_events() {
  glfwPollEvents();
  return !glfwWindowShouldClose(window);
}

void window_swap_buffers() {
  glfwSwapBuffers(window);
}

void window_terminate() {
  glfwDestroyWindow(window);
  glfwTerminate();
  VALLY_TRACE("Window subsystem terminated");
}

void window_set_key_callback(void *callback) {
  glfwSetKeyCallback(window, callback);
}

void window_set_mouse_button_callback(void *callback) {
  glfwSetMouseButtonCallback(window, callback);
}

void window_set_cursor_position_callback(void *callback) {
  glfwSetCursorPosCallback(window, callback);
}