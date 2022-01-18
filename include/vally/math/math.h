/*********************************************************************
 * math.h                                                            *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_MATH_H_
#define VALLY_MATH_H_

#include <vally/config.h>
#include <vally/math/math_types.h>

#define V_PI 3.141592653589793F
#define V_2PI V_PI * 2.0F
#define V_PI_2 V_PI / 2.0F
#define V_PI_3 V_PI / 3.0F
#define V_PI_4 V_PI / 4.0F
#define V_SQRT2 1.41421356237F

#define LERP(w, v1, v2) ((1.0 - (w)) * (v1) + (w) * (v2))

#define vector2f_create(x, y) ((vector2f){x, y})
#define vector3f_create(x, y, z) ((vector3f){x, y, z})
#define vector2i_create(x, y) ((vector2i){x, y})
#define vector3i_create(x, y, z) ((vector3i){x, y, z})

#define vector2f_zero vector2f_create(0.0f, 0.0f)
#define vector2f_one vector2f_create(1.0f, 1.0f)
#define vector2f_right vector2f_create(1.0f, 0.0f)
#define vector2f_left vector2f_create(-1.0f, 0.0f)
#define vector2f_up vector2f_create(0.0f, 1.0f)
#define vector2f_down vector2f_create(0.0f, -1.0f)

VALLY_API f32 vsin(f32 x);
VALLY_API f32 vcos(f32 x);
VALLY_API f32 vtan(f32 x);
VALLY_API f32 vasin(f32 x);
VALLY_API f32 vacos(f32 x);
VALLY_API f32 vatan(f32 x);
VALLY_API f32 vsqrt(f32 x);
VALLY_API f32 vabs(f32 x);

/* vector2f */
static inline vector2f vector2f_add(vector2f a, vector2f b) {
  return vector2f_create(a.x + b.x, a.y + b.y);
}

static inline vector2f vector2f_sub(vector2f a, vector2f b) {
  return vector2f_create(a.x - b.x, a.y - b.y);
}

static inline vector2f vector2f_mul(vector2f a, vector2f b) {
  return vector2f_create(a.x * b.x, a.y * b.y);
}

static inline vector2f vector2f_muls(vector2f vector, f32 scalar) {
  return vector2f_create(vector.x * scalar, vector.y * scalar);
}

static inline vector2f vector2f_divs(vector2f vector, f32 scalar) {
  return vector2f_create(vector.x / scalar, vector.y / scalar);
}

static inline vector2f vector2f_div(vector2f a, vector2f b) {
  return vector2f_create(a.x / b.x, a.y / b.y);
}

static inline f32 vector2f_length(vector2f vector) {
  return vsqrt(vector.x * vector.x + vector.y * vector.y);
}

static inline vector2f vector2f_normalized(vector2f vector) {
  const f32 length = vector2f_length(vector);
  if (length != 0.0f) {
    return vector2f_divs(vector, vector2f_length(vector));
  } else {
    return vector;
  }
}

static inline void vector2f_normalize(vector2f *vector) {
  const f32 length = vector2f_length(*vector);
  if (length != 0.0f) {
    vector->x /= length;
    vector->y /= length;
  }
}

static inline f32 vector2f_distance(vector2f a, vector2f b) {
  return vector2f_length(vector2f_sub(a, b));
}

/* vector3f */
static inline vector3f vector3f_add(vector3f a, vector3f b) {
  return vector3f_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

static inline vector3f vector3f_sub(vector3f a, vector3f b) {
  return vector3f_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

static inline vector3f vector3f_cross(vector3f a, vector3f b) {
  return vector3f_create((a.y * b.z - a.z * b.y), ( a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x));
}

static inline f32 vector3f_dot(vector3f a, vector3f b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline vector3f vector3f_mul(vector3f a, vector3f b) {
  return vector3f_create(a.x * b.x, a.y * b.y, a.z * b.z);
}

static inline vector3f vector3f_div(vector3f a, vector3f b) {
  return vector3f_create(a.x / b.x, a.y / b.y, a.z / b.z);
}

static inline vector3f vector3f_muls(vector3f vector, f32 scalar) {
  return vector3f_create(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

static inline vector3f vector3f_divs(vector3f vector, f32 scalar) {
  return vector3f_create(vector.x / scalar, vector.y / scalar, vector.z / scalar);
}

static inline f32 vector3f_length(vector3f vector) {
  return vsqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

static inline vector3f vector3f_normalized(vector3f vector) {
  return vector3f_divs(vector, vector3f_length(vector));
}

static inline void vector3f_normalize(vector3f *vector) {
  *vector = vector3f_normalized(*vector);
}

static inline f32 vector3f_distance(vector3f a, vector3f b) {
  return vector3f_length(vector3f_sub(a, b));
}

static inline vector2i vector2i_add(vector2i a, vector2i b) {
  return vector2i_create(a.x + b.x, a.y + b.y);
}

static inline vector3i vector3i_add(vector3i a, vector3i b) {
  return vector3i_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

static inline vector2i vector2i_sub(vector2i a, vector2i b) {
  return vector2i_create(a.x - b.x, a.y - b.y);
}

static inline vector3i vector3i_sub(vector3i a, vector3i b) {
  return vector3i_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

#endif // VALLY_MATH_H_