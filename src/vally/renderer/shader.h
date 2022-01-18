/*********************************************************************
 * shader.h                                                          *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_SHADER_H_
#define VALLY_SHADER_H_

#include <cglm/cglm.h>
#include <cglm/struct.h>

#include <vally/config.h>

typedef struct {
  u32 id;
  b8 attached;
} shader;

shader *shader_create(const char *vertex_path, const char *fragment_path);
void shader_destroy(shader *shdr);

void shader_attach(shader *shdr);
void shader_deattach(shader *shdr);

void shader_send_float(shader *shdr, const char *name, f32 value);
void shader_send_float_array(shader *shdr, const char *name, i32 count, const f32 *array);
void shader_send_vec2(shader *shdr, const char *name, vec2s vector);
void shader_send_vec3(shader *shdr, const char *name, vec3s vector);
void shader_send_vec4(shader *shdr, const char *name, vec4s vector);
void shader_send_int(shader *shdr, const char *name, int value);
void shader_send_int_array(shader *shdr, const char *name, i32 count, const i32 *array);
void shader_send_mat4(shader *shdr, const char *name, mat4s matrix);

#endif // VALLY_SHADER_H_
