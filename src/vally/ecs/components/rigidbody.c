/*********************************************************************
 * rigidbody.c                                                       *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#include "vally/ecs/ecs_types.h"
#include <vally/ecs/components/rigidbody.h>

#include <stddef.h>

#include <vally/core/logger.h>

typedef struct {
  rigidbody components[ECS_MAX_COMPONENTS];
} rigidbody_state;

static rigidbody_state state;

void ecs_rigidbody_add(entity entity) {
  if (entity == ECS_NULL_ENTITY || !ecs_is_alive(entity)) {
    return;
  }

  rigidbody rb;
  rb.is_static = FALSE;
  rb.gravity = 4.9f;
  rb.mass = 1.0f;
  rb.velocity = vector2f_zero;

  state.components[entity] = rb;
  ecs_component_add(entity, ECS_RIGIDBODY_COMPONENT);
}

rigidbody *ecs_rigidbody_get(entity entity) {
  if (entity == ECS_NULL_ENTITY || !ecs_is_alive(entity) || !ecs_component_has(entity, ECS_RIGIDBODY_COMPONENT)) {
    return NULL;
  }

  return &state.components[entity];
}

void ecs_rigidbody_update(f32 delta_time) {
  for (entity e = 0; e < ecs_get_last(); e++) {
    if (ecs_is_alive(e) && ecs_component_has(e, ECS_RIGIDBODY_COMPONENT | ECS_TRANSFORM_COMPONENT)) {
      rigidbody *rb = &state.components[e];
      vector2f move = vector2f_create(rb->velocity.x, 0.0f);
      transform *t = ecs_transform_get(e);
      t->position = vector2f_add(t->position, move);
      if (!rb->is_static) {
        t->position.y += rb->mass * rb->gravity;
      }
    }
  }
}

