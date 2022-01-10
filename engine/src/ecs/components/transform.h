#ifndef VALLY_ECS_COMPONENTS_TRANSFORM_H_
#define VALLY_ECS_COMPONENTS_TRANSFORM_H_

#include "defines.h"
#include "ecs/ecs.h"
#include "math/vmath.h"

typedef struct {
  entity entity;
  vector2f position;
  vector2f scale;
} transform;

VALLY_DLL void ecs_transform_add(entity entity, vector2f position, vector2f scale);

VALLY_DLL transform *ecs_transform_get(entity entity);

#endif // !VALLY_ECS_COMPONENTS_TRANSFORM_H_