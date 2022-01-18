/*********************************************************************
 * transform.c                                                       *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#include <vally/ecs/components/transform.h>

#include <stddef.h>

typedef struct {
  transform components[ECS_MAX_COMPONENTS];
} transform_system;

static transform_system system;

void ecs_transform_add(entity entity, vector2f position, vector2f scale) {
  if (entity == ECS_NULL_ENTITY) {
    return;
  }

  transform component;
  component.entity = entity;
  component.position = position;
  component.scale = scale;

  system.components[entity] = component;
  ecs_component_add(entity, ECS_TRANSFORM_COMPONENT);
}

transform *ecs_transform_get(entity entity) {
  if (entity == ECS_NULL_ENTITY || !ecs_component_has(entity, ECS_TRANSFORM_COMPONENT)) {
    return NULL;
  }

  return &system.components[entity];
}