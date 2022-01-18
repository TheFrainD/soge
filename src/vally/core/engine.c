/*********************************************************************
 * engine.c                                                          *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#include <vally/core/engine.h>

#include <vally/core/assertions.h>
#include <vally/core/logger.h>
#include <vally/core/window.h>
#include <vally/core/event.h>
#include <vally/core/input.h>
#include <vally/core/time.h>
#include <vally/resources/resources.h>
#include <vally/renderer/renderer.h>
#include <vally/ecs/ecs.h>

/**
 * @brief Engine state struct.
 * 
 * Contains all neccessary data.
 * 
 */
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

static b8 engine_window_resized(u16 code, void *sender, void *listener, event_context context) {
  state.width = (i32)context.data.f32[0];
  state.height = (i32)context.data.f32[1];

  return TRUE;
}

b8 engine_create(i16 width, i16 height, char *title) {
  if (initialized) {
    LOG_ERROR("engine_create cannot be called more than once");
    return FALSE;
  }

  state.is_runing = TRUE;
  state.is_suspended = FALSE;

  // Initialize engine subsystems
  logger_init();
  
  LOG_INFO("VALLY starts");

  state.width = width;
  state.height = height;
  if (!window_create(width, height, title)) {
    LOG_FATAL("Could not initialize the window system!");
    return FALSE;
  }

  if (!event_init()) {
    LOG_ERROR("Could not initialize the event system!");
    return FALSE;
  }
  
  if (!input_init()) {
    LOG_ERROR("Could not initialize the input system!");
    return FALSE;
  }

  if (!resources_init()) {
    LOG_ERROR("Could not initialize the resource system!");
    return FALSE;
  }

  if (!renderer_init()) {
    LOG_ERROR("Could not initialize the renderer system!");
    return FALSE;
  }

  if (!ecs_init()) {
    LOG_ERROR("Could not initialize ECS!");
    return FALSE;
  }

  state.last_time = time_now();

  event_subscribe(EVENT_CODE_WINDOW_RESIZED, &state, engine_window_resized);

  initialized = TRUE;

  return TRUE;
}

b8 engine_run(engine_start start, engine_update update, engine_render render) {
  if (!start || !update || !render) {
    LOG_FATAL("Could not run the engine! Functions must not be NULL!");
    return FALSE;
  }

  start();

  // Main loop
  while (state.is_runing) {
    f64 current_time = time_now();
    f64 delta_time = current_time - state.last_time;

    if (!window_poll_events()) {
      state.is_runing = FALSE;
    }

    update(delta_time);

    ecs_rigidbody_update(delta_time);
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
  LOG_INFO("Shutting down");

  return TRUE;
}
