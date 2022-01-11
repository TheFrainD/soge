#ifndef VALLY_ECS_ECS_H_
#define VALLY_ECS_ECS_H_

#include <vally/config.h>
#include <vally/ecs/ecs_types.h>
#include <vally/ecs/components/spriterenderer.h>
#include <vally/ecs/components/transform.h>
#include <vally/ecs/components/animator.h>

#define ECS_NULL_ENTITY -1
#define ECS_MAX_ENTITIES 1000
#define ECS_MAX_COMPONENTS ECS_MAX_ENTITIES

b8 ecs_init();

VALLY_API entity ecs_entity_create();

VALLY_API void ecs_component_add(entity entity, component_mask mask);

VALLY_API void ecs_component_remove(entity entity, component_mask mask);

b8 ecs_component_has(entity entity, component_mask mask);

entity ecs_get_last();

#define ecs_is_alive(entity)  ecs_component_has(entity, ECS_ALIVE)

#endif // !VALLY_ECS_ECS_H_