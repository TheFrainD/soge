#include "engine.h"

#include "core/assertions.h"
#include "core/logger.h"
#include "core/window.h"
#include "core/event.h"
#include "core/input.h"
#include "resources/resources.h"
#include "renderer/renderer.h"

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
    VALLY_ERROR("engine_create cannot be called more than once");
    return FALSE;
  }

  // Init subsystems
  logger_init();

  VALLY_INFO("VALLY starts");

  _engine_state.is_runing = TRUE;
  _engine_state.is_suspended = FALSE;

  _engine_state.width = width;
  _engine_state.height = height;
  if (!window_create(width, height, title)) {
    return FALSE;
  }

  if (!event_init()) {
    VALLY_ERROR("Could not initialize the event system!");
    return FALSE;
  }

  input_init();

  if (!resources_init()) {
    VALLY_ERROR("Could not initialize the resource system!");
    return FALSE;
  }

  if (!renderer_init()) {
    VALLY_ERROR("Could not initialize the renderer system!");
    return FALSE;
  }

  initialized = TRUE;

  return TRUE;
}

b8 engine_run(engine_start start, engine_update update, engine_render render) {
  if (!start || !update || !render) {
    VALLY_FATAL("Could not run the engine! Functions must not be NULL!");
    return FALSE;
  }

  start();

  while (_engine_state.is_runing) {
    if (!window_poll_events()) {
      _engine_state.is_runing = FALSE;
    }

    update((f32)0);

    renderer_clear_screen();
    renderer_begin_batch();
    render((f32)0);
    renderer_end_batch();
    renderer_flush();

    window_swap_buffers();
  }

  _engine_state.is_runing = FALSE;

  event_terminate();
  input_terminate();
  renderer_terminate();
  resources_terminate();
  window_terminate();
  VALLY_INFO("Shutting down");

  return TRUE;
}
