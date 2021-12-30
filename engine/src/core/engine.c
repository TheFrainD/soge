#include "engine.h"

#include "assertions.h"
#include "logger.h"
#include "window.h"

typedef struct {
  b8 is_runing;
  b8 is_suspended;
  i16 width;
  i16 height;
  f64 last_time;
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

  if (!window_create(width, height, title)) {
    return FALSE;
  }

  initialized = TRUE;

  return TRUE;
}

b8 engine_run() {
  while (_engine_state.is_runing) {
    if (!window_poll_events()) {
      _engine_state.is_runing = FALSE;
    }
  }

  _engine_state.is_runing = FALSE;

  window_terminate();
  SOGE_INFO("Shutting down");

  return TRUE;
}