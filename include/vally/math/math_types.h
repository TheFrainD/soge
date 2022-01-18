/*********************************************************************
 * math_types.h                                                      *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_MATH_TYPES_H_
#define VALLY_MATH_TYPES_H_

#include <vally/config.h>

typedef struct {
  f32 x;
  f32 y;
} vector2f;

typedef struct {
  f32 x;
  f32 y;
  f32 z;
} vector3f;

typedef struct {
  i32 x;
  i32 y;
} vector2i;

typedef struct {
  i32 x;
  i32 y;
  i32 z;
} vector3i;

#endif // VALLY_MATH_TYPES_H_