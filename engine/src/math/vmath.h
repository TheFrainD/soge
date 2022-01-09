#ifndef VALLY_MATH_VMATH_H_
#define VALLY_MATH_VMATH_H_

#include "defines.h"
#include "math/vmath_types.h"

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

#define vector2f_zero() vector2f_create(0.0f, 0.0f)
#define vector2f_one() vector2f_create(1.0f, 1.0f)
#define vector2f_right() vector2f_create(1.0f, 0.0f)
#define vector2f_left() vector2f_create(-1.0f, 0.0f)
#define vector2f_up() vector2f_create(0.0f, 1.0f)
#define vector2f_down() vector2f_create(0.0f, -1.0f)

VALLY_DLL f32 vsin(f32 x);
VALLY_DLL f32 vcos(f32 x);
VALLY_DLL f32 vtan(f32 x);
VALLY_DLL f32 vasin(f32 x);
VALLY_DLL f32 vacos(f32 x);
VALLY_DLL f32 vatan(f32 x);
VALLY_DLL f32 vsqrt(f32 x);
VALLY_DLL f32 vabs(f32 x);

/* vector2f */
VALLY_INLINE vector2f vector2f_add(vector2f a, vector2f b) {
  return vector2f_create(a.x + b.x, a.y + b.y);
}

VALLY_INLINE vector2f vector2f_sub(vector2f a, vector2f b) {
  return vector2f_create(a.x - b.x, a.y - b.y);
}

VALLY_INLINE vector2f vector2f_mul(vector2f a, vector2f b) {
  return vector2f_create(a.x * b.x, a.y * b.y);
}

VALLY_INLINE vector2f vector2f_muls(vector2f vector, f32 scalar) {
  return vector2f_create(vector.x * scalar, vector.y * scalar);
}

VALLY_INLINE vector2f vector2f_divs(vector2f vector, f32 scalar) {
  return vector2f_create(vector.x / scalar, vector.y / scalar);
}

VALLY_INLINE vector2f vector2f_div(vector2f a, vector2f b) {
  return vector2f_create(a.x / b.x, a.y / b.y);
}

VALLY_INLINE f32 vector2f_length(vector2f vector) {
  return vsqrt(vector.x * vector.x + vector.y * vector.y);
}

VALLY_INLINE vector2f vector2f_normalized(vector2f vector) {
  const f32 length = vector2f_length(vector);
  if (length != 0.0f) {
    return vector2f_divs(vector, vector2f_length(vector));
  } else {
    return vector;
  }
}

VALLY_INLINE void vector2f_normalize(vector2f *vector) {
  const f32 length = vector2f_length(*vector);
  if (length != 0.0f) {
    vector->x /= length;
    vector->y /= length;
  }
}

VALLY_INLINE f32 vector2f_distance(vector2f a, vector2f b) {
  return vector2f_length(vector2f_sub(a, b));
}

/* vector3f */
VALLY_INLINE vector3f vector3f_add(vector3f a, vector3f b) {
  return vector3f_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

VALLY_INLINE vector3f vector3f_sub(vector3f a, vector3f b) {
  return vector3f_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

VALLY_INLINE vector3f vector3f_cross(vector3f a, vector3f b) {
  return vector3f_create((a.y * b.z - a.z * b.y), ( a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x));
}

VALLY_INLINE f32 vector3f_dot(vector3f a, vector3f b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

VALLY_INLINE vector3f vector3f_mul(vector3f a, vector3f b) {
  return vector3f_create(a.x * b.x, a.y * b.y, a.z * b.z);
}

VALLY_INLINE vector3f vector3f_div(vector3f a, vector3f b) {
  return vector3f_create(a.x / b.x, a.y / b.y, a.z / b.z);
}

VALLY_INLINE vector3f vector3f_muls(vector3f vector, f32 scalar) {
  return vector3f_create(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

VALLY_INLINE vector3f vector3f_divs(vector3f vector, f32 scalar) {
  return vector3f_create(vector.x / scalar, vector.y / scalar, vector.z / scalar);
}

VALLY_INLINE f32 vector3f_length(vector3f vector) {
  return vsqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

VALLY_INLINE vector3f vector3f_normalized(vector3f vector) {
  return vector3f_divs(vector, vector3f_length(vector));
}

VALLY_INLINE void vector3f_normalize(vector3f *vector) {
  *vector = vector3f_normalized(*vector);
}

VALLY_INLINE f32 vector3f_distance(vector3f a, vector3f b) {
  return vector3f_length(vector3f_sub(a, b));
}

VALLY_INLINE vector2i vector2i_add(vector2i a, vector2i b) {
  return vector2i_create(a.x + b.x, a.y + b.y);
}

VALLY_INLINE vector3i vector3i_add(vector3i a, vector3i b) {
  return vector3i_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

VALLY_INLINE vector2i vector2i_sub(vector2i a, vector2i b) {
  return vector2i_create(a.x - b.x, a.y - b.y);
}

VALLY_INLINE vector3i vector3i_sub(vector3i a, vector3i b) {
  return vector3i_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

#endif // !VALLY_MATH_VMATH_H_