#include "engine.h"

// TODO: remove
#include <glad/glad.h>

#include "assertions.h"
#include "logger.h"
#include "window.h"

typedef struct {
  b8 is_runing;
  b8 is_suspended;
  i16 width;
  i16 height;
  f64 last_time;

  // Functions
  engine_start start;
  engine_update update;
  engine_render render;
} engine_state;

static b8 initialized = FALSE;
static engine_state _engine_state;

b8 engine_create(i16 width, i16 height, const char *title) {
  if (initialized) {
    SOGE_ERROR("engine_create cannot be called more than once");
    return FALSE;
  }

  // Init subsystems
  logger_init();

  SOGE_INFO("SOGE starts");

  _engine_state.is_runing = TRUE;
  _engine_state.is_suspended = FALSE;

  _engine_state.width = width;
  _engine_state.height = height;
  if (!window_create(width, height, title)) {
    return FALSE;
  }

  initialized = TRUE;

  return TRUE;
}

b8 engine_run(engine_start start, engine_update update, engine_render render) {
  if (!start || !update || !render) {
    SOGE_FATAL("Could not run the engine! Functions must not be NULL!");
    return FALSE;
  }

  start();

  while (_engine_state.is_runing) {
    if (!window_poll_events()) {
      _engine_state.is_runing = FALSE;
    }

    update((f32)0);

    glClear(GL_COLOR_BUFFER_BIT);
    render((f32)0);
    window_swap_buffers();
  }

  _engine_state.is_runing = FALSE;

  window_terminate();
  SOGE_INFO("Shutting down");

  return TRUE;
}