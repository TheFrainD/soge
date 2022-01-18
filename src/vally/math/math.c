/*********************************************************************
 * math.c                                                            *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#include <vally/math/math.h>

#include <math.h>

f32 vsin(f32 x) {
  return sinf(x);
}

f32 vcos(f32 x) {
  return cosf(x);
}

f32 vtan(f32 x) {
  return tanf(x);
}

f32 vasin(f32 x) {
  return asinf(x);
}

f32 vacos(f32 x) {
  return acosf(x);
}

f32 vatan(f32 x) {
  return atanf(x);
}

f32 vsqrt(f32 x) {
  return sqrtf(x);
}

f32 vabs(f32 x) {
  return fabsf(x);
}