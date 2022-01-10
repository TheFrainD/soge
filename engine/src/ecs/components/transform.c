#include "ecs/components/transform.h"

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