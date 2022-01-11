//================================================================================
// Vally 0.1indev
//--------------------------------------------------------------------------------
// Copyright (c) 2022 Dmytro Zykov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//=================================================================================

#include <vally/core/engine.h>

//-----Internal includes----------
#include <vally/core/assertions.h>
#include <vally/core/logger.h>
#include <vally/core/window.h>
#include <vally/core/event.h>
#include <vally/core/input.h>
#include <vally/core/time.h>
#include <vally/resources/resources.h>
#include <vally/renderer/renderer.h>
#include <vally/ecs/ecs.h>
//--------------------------------

// Engine state struct.
// Contains all vital data
typedef struct {
  b8 is_runing;
  b8 is_suspended;
  i16 width;  /* Not sure that it's needed */
  i16 height;
  f64 last_time;

  // Functions
  engine_start start;
  engine_update update;
  engine_render render;
} engine_state;

// Initialized flag
static b8 initialized = FALSE;
static engine_state state;

b8 engine_create(i16 width, i16 height, const char *title) {
  if (initialized) {
    VALLY_ERROR("engine_create cannot be called more than once");
    return FALSE;
  }

  state.is_runing = TRUE;
  state.is_suspended = FALSE;

  //=======Initialze subsystems===========
  logger_init();

  VALLY_INFO("VALLY starts");

  state.width = width;
  state.height = height;
  if (!window_create(width, height, title)) {
    VALLY_FATAL("Could not initialize the window system!");
    return FALSE;
  }

  if (!event_init()) {
    VALLY_ERROR("Could not initialize the event system!");
    return FALSE;
  }

  if (!input_init()) {
    VALLY_ERROR("Could not initialize the input system!");
    return FALSE;
  }

  if (!resources_init()) {
    VALLY_ERROR("Could not initialize the resource system!");
    return FALSE;
  }

  if (!renderer_init()) {
    VALLY_ERROR("Could not initialize the renderer system!");
    return FALSE;
  }

  if (!ecs_init()) {
    VALLY_ERROR("Could not initialize ECS!");
    return FALSE;
  }
  //=====================================


  state.last_time = time_now();

  initialized = TRUE;

  return TRUE;
}

b8 engine_run(engine_start start, engine_update update, engine_render render) {
  if (!start || !update || !render) {
    VALLY_FATAL("Could not run the engine! Functions must not be NULL!");
    return FALSE;
  }

  start();

  while (state.is_runing) {
    f64 current_time = time_now();
    f64 delta_time = current_time - state.last_time;

    if (!window_poll_events()) {
      state.is_runing = FALSE;
    }

    update(delta_time);

    ecs_animator_update(delta_time);

    renderer_clear_screen();
    renderer_begin_batch();
    ecs_spriterenderer_update();
    render(delta_time);
    renderer_end_batch();
    renderer_flush();

    window_swap_buffers();

    state.last_time = current_time;
  }

  state.is_runing = FALSE;

  // Termiante all systems
  event_terminate();
  input_terminate();
  renderer_terminate();
  resources_terminate();
  window_terminate();
  VALLY_INFO("Shutting down");

  return TRUE;
}
