/*********************************************************************
 * ecs.c                                                             *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#include <vally/ecs/ecs.h>

#include <vally/core/logger.h>
#include <vally/ecs/components/transform.h>
#include <vally/math/math.h>

typedef struct {
  entity last;
  component_mask masks[ECS_MAX_COMPONENTS];
} ecs_state;

static b8 initialized = FALSE;
static ecs_state state;

b8 ecs_init() {
  if (initialized) {
    return FALSE;
  }

  state.last = 0;
  initialized = TRUE;

  LOG_TRACE("ECS initialized");

  return TRUE;
}

entity ecs_entity_create() {
  if (!initialized) {
    return ECS_NULL_ENTITY;
  }

  entity entity = state.last++;
  state.masks[entity] = ECS_ALIVE;

  ecs_transform_add(entity, vector2f_zero, vector2f_one);

  return entity;
}

void ecs_component_add(entity entity, component_mask mask) {
  if (!initialized || entity == ECS_NULL_ENTITY) {
    return;
  }

  state.masks[entity] |= mask;
}

void ecs_component_remove(entity entity, component_mask mask) {
  if (!initialized || entity == ECS_NULL_ENTITY) {
    return;
  }

  state.masks[entity] &= ~mask;
}

b8 ecs_component_has(entity entity, component_mask mask) {
  if (!initialized || entity == ECS_NULL_ENTITY) {
    return FALSE;
  }

  return state.masks[entity] & mask;
}

entity ecs_get_last() {
  if (!initialized) {
    return ECS_NULL_ENTITY;
  }

  return state.last;
}