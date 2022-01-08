#include <core/window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <core/logger.h>

typedef struct {
  GLFWwindow *window;
  i32 width;
  i32 height;
  char *title;
} window_state;

static b8 initialized = FALSE;
static window_state state;

b8 window_create(i32 width, i32 height, const char* title) {
  if (initialized) {
    return FALSE;
  }
  state.width = width;
  state.height = height;
  state.title = title;

  if (!glfwInit()) {
    VALLY_FATAL("Could not initialize GLFW!");
    return FALSE;
  }
  VALLY_TRACE("GLFW initialized");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  state.window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!state.window) {
    VALLY_FATAL("Could not create window!");
    return FALSE;
  }
  VALLY_TRACE("Window created");
  glfwMakeContextCurrent(state.window);
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
  return !glfwWindowShouldClose(state.window);
}

void window_swap_buffers() {
  glfwSwapBuffers(state.window);
}

void window_terminate() {
  glfwDestroyWindow(state.window);
  glfwTerminate();
  VALLY_TRACE("Window subsystem terminated");
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
