/*********************************************************************
 * buffer.h                                                          *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_BUFFER_H_
#define VALLY_BUFFER_H_

#include <vally/config.h>

// Vertex layout
typedef struct {
  f32 pos[2];
  f32 color[4];
  f32 uv[2];
  f32 tex_id;
} vertex;

typedef struct {
  u32 vao;
  u32 vbo;
  u32 ebo;
} buffer;

buffer *buffer_create();
void buffer_destroy(buffer *buf);

void buffer_bind(buffer *buf);
void buffer_unbind();
void buffer_set_data(buffer *buf, i32 size, const void *data);

#endif // VALLY_BUFFER_H_