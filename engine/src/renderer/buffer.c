#include "buffer.h"

#include <stddef.h>
#include <stdlib.h>

#include <glad/glad.h>

#include "core/logger.h"
#include "renderer/renderer.h"
#include "resources/resources.h"

buffer *buffer_create() {
  buffer *buf = (buffer *)malloc(sizeof(buffer));

  glGenVertexArrays(1, &buf->vao);
  glGenBuffers(1, &buf->vbo);
  glGenBuffers(1, &buf->ebo);

  glBindVertexArray(buf->vao);

  glBindBuffer(GL_ARRAY_BUFFER, buf->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * RENDERER_MAX_VERTEX, NULL, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)offsetof(vertex, pos));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)offsetof(vertex, color));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)offsetof(vertex, uv));
  glEnableVertexAttribArray(2);

  glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)offsetof(vertex, tex_id));
  glEnableVertexAttribArray(3);

  u32 indices[RENDERER_MAX_INDEX];
  u32 offset = 0;
  for (int i = 0; i < RENDERER_MAX_INDEX; i += 6) {
    indices[i + 0] = 0 + offset;
    indices[i + 1] = 1 + offset;
    indices[i + 2] = 2 + offset;

    indices[i + 3] = 2 + offset;
    indices[i + 4] = 3 + offset;
    indices[i + 5] = 0 + offset;

    offset += 4;
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  resources_add(buf, buffer_destroy);

  return buf;
}

void buffer_destroy(buffer *buf) {
  glDeleteVertexArrays(1, &buf->vao);
  glDeleteBuffers(1, &buf->vbo);
  glDeleteBuffers(1, &buf->ebo);
}

void buffer_bind(buffer *buf) {
  glBindVertexArray(buf->vao);
}

void buffer_unbind() {
  glBindVertexArray(0);
}
void buffer_set_data(buffer *buf, i32 size, const void *data) {
  glBindBuffer(GL_ARRAY_BUFFER, buf->vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}