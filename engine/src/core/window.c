#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logger.h"

static GLFWwindow *window;

b8 window_create(i32 width, i32 height, const char* title) {
  if (!glfwInit()) {
    SOGE_FATAL("Could not initialize GLFW!");
    return FALSE;
  }
  SOGE_TRACE("GLFW initialized");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(640, 480, "soge", NULL, NULL);
  if (!window) {
    SOGE_FATAL("Could not create window!");
    return FALSE;
  }
  SOGE_TRACE("Window created");
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    SOGE_FATAL("Could not initialize glad!");
    return FALSE;
  }
  SOGE_TRACE("glad initialized");

  return TRUE;
}

b8 window_poll_events() {
  glfwPollEvents();
  return !glfwWindowShouldClose(window);
}

void window_terminate() {
  glfwDestroyWindow(window);
  glfwTerminate();
}