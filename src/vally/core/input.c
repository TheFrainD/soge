#include <vally/core/input.h>

#include <string.h>

#include <GLFW/glfw3.h>

#include <vally/core/window.h>
#include <vally/core/event.h>
#include <vally/core/logger.h>

typedef struct {
  b8 keys[KEYS_MAX_KEYS];
} keyboard_state;

typedef struct {
  b8 buttons[MOUSE_BUTTON_MAX];
  f64 x;
  f64 y;
  f64 prev_x;
  f64 prev_y;
} mouse_state;

typedef struct {
  keyboard_state keyboard;
  mouse_state mouse;
} input_state;

static b8 initialized = FALSE;
static input_state state;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
  if (state.keyboard.keys[key] != action) {
    state.keyboard.keys[key] = action;

    event_context context;
    context.data.u16[0] = key;
    event_publish(action ? EVENT_CODE_KEY_PRESSED : EVENT_CODE_KEY_RELEASED, NULL, context);
  }
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mode) {
  if (state.mouse.buttons[button] != action) {
    state.mouse.buttons[button] = action;

    event_context context;
    context.data.u16[0] = button;
    event_publish(action ? EVENT_CODE_MOUSE_BUTTON_PRESSED : EVENT_CODE_MOUSE_BUTTON_RELEASED, NULL, context);
  }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
  if (state.mouse.x != xpos || state.mouse.y != ypos) {
    state.mouse.prev_x = state.mouse.x;
    state.mouse.prev_y = state.mouse.y;
    state.mouse.x = xpos;
    state.mouse.y = ypos;

    event_context context;
    context.data.f64[0] = xpos;
    context.data.f64[1] = ypos;
    event_publish(EVENT_CODE_MOUSE_MOVED, NULL, context);
  }
}

b8 input_init() {
  memset(state.keyboard.keys, FALSE, sizeof(state.keyboard.keys));
  memset(state.mouse.buttons, FALSE, sizeof(state.mouse.buttons));

  window_set_key_callback(key_callback);
  window_set_mouse_button_callback(mouse_button_callback);
  window_set_cursor_position_callback(cursor_position_callback);

  initialized = TRUE;
  VALLY_TRACE("Input system initialized");

  return TRUE;
}
void input_terminate() {
  initialized = FALSE;
  VALLY_TRACE("Input system terminated");
}

b8 input_key_pressed(u16 key) {
  if (!initialized) {
    return FALSE;
  }

  return state.keyboard.keys[key];
}

b8 input_key_released(u16 key) {
  if (!initialized) {
    return FALSE;
  }
  
  return !state.keyboard.keys[key];
}

b8 input_mouse_button_pressed(u16 button) {
  if (!initialized) {
    return FALSE;
  }
  
  return state.mouse.buttons[button];
}

b8 input_mouse_button_released(u16 button) {
  if (!initialized) {
    return FALSE;
  }
  
  return !state.mouse.buttons[button];
}

void input_mouse_position(f64 *x, f64 *y) {
  if (!initialized) {
    *x = 0;
    *y = 0;
    return;
  }
  
  *x = state.mouse.x;
  *y = state.mouse.y;
}
void input_mouse_prev_position(f64 *x, f64 *y) {
  if (!initialized) {
    *x = 0;
    *y = 0;
    return;
  }

  *x = state.mouse.prev_x;
  *y = state.mouse.prev_y;
}