/*********************************************************************
 * transforn.h                                                       *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_TRANSFORM_H_
#define VALLY_TRANSFORM_H_

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

#endif // VALLY_TRANSFORM_H_