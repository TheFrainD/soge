#ifndef VALLY_ECS_COMPONENTS_TRANSFORM_H_
#define VALLY_ECS_COMPONENTS_TRANSFORM_H_

#include <vally/config.h>
#include <vally/ecs/ecs.h>
#include <vally/math/math.h>

typedef struct {
  entity entity;
  vector2f position;
  vector2f scale;
} transform;

VALLY_API void ecs_transform_add(entity entity, vector2f position, vector2f scale);

VALLY_API transform *ecs_transform_get(entity entity);

#endif // !VALLY_ECS_COMPONENTS_TRANSFORM_H_