/*********************************************************************
 * rigidbody.h                                                       *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_RIGIDBODY_H_
#define VALLY_RIGIDBODY_H_

#include <vally/config.h>

#include <vally/ecs/ecs.h>
#include <vally/math/math.h>

/**
 * @bried A rigidbody struct.
 *
 */
typedef struct {
  b8 is_static;
  f32 gravity;
  f32 mass;
  vector2f velocity;
} rigidbody;

/**
 * @brief Adds rigidbody component to entity.
 *
 */
VALLY_API void ecs_rigidbody_add(entity entity);

/**
 * @brief Gets an instance of rigidbody component.
 *
 * @param entity entity
 * @return rigidbody component or NULL if entity does not have this component 
 *
 */
VALLY_API rigidbody *ecs_rigidbody_get(entity entity);

void ecs_rigidbody_update(f32 delta_time);

#endif // VALLY_RIGIDBODY_H_
