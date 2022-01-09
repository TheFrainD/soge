#ifndef VALLY_RENDERER_BUFFER_H_
#define VALLY_RENDERER_BUFFER_H_

#include "defines.h"

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

#endif // !VALLY_RENDERER_BUFFER_H_