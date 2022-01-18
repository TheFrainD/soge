/*********************************************************************
 * ecs_types.h                                                       *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_ECS_TYPES_H_
#define VALLY_ECS_TYPES_H_

#include <vally/config.h>

typedef i32 entity;

typedef enum {
  ECS_ALIVE = BIT_MASK(0),
  ECS_TRANSFORM_COMPONENT = BIT_MASK(1),
  ECS_SPRITERENDERER_COMPONENT = BIT_MASK(2),
  ECS_RIGIDBODY_COMPONENT = BIT_MASK(3),
  ECS_ANIMATOR_COMPONENT = BIT_MASK(4),
} component_mask;

#endif // VALLY_ECS_TYPES_H_