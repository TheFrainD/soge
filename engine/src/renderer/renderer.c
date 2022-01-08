#include "renderer.h"

#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>

#include "core/event.h"
#include "core/logger.h"
#include "core/window.h"
#include "renderer/texture.h"
#include "renderer/shader.h"
#include "renderer/camera.h"
#include "renderer/buffer.h"

#define RENDERER_MAX_QUADS 1000
#define RENDERER_MAX_VERTEX RENDERER_MAX_QUADS * 4
#define RENDERER_MAX_INDEX RENDERER_MAX_QUADS * 6
#define RENDERER_MAX_TEXTURES 16

typedef struct {
  shader shader_;
  
  u32 vao;
  u32 vbo;
  u32 ebo;

  texture tex_white;
  texture *textures[RENDERER_MAX_TEXTURES];
  u32 sampler[RENDERER_MAX_TEXTURES];
  u32 tex_slot;

  vertex quad_buffer[RENDERER_MAX_VERTEX];
  vertex *quad_buffer_ptr;

  u32 index_count;
} renderer_state;

static b8 initialized = FALSE;
static renderer_state state;

static b8 renderer_update_projection(u16 code, void *sender, void *listener, event_context context) {
  shader_send_mat4(&state.shader_, "u_proj", camera_update_projection(context.data.f32[0], context.data.f32[1]));
  return TRUE;
}

static b8 renderer_update_view(u16 code, void *sender, void *listener, event_context context) {
  shader_send_mat4(&state.shader_, "u_view", camera_update_view());
  return TRUE;
}

b8 renderer_init() {
  if (initialized) {
    return FALSE;
  }

  state.shader_ = shader_create("../assets/shaders/vertex.glsl", "../assets/shaders/fragment.glsl");

  glGenVertexArrays(1, &state.vao);
  glGenBuffers(1, &state.vbo);
  glGenBuffers(1, &state.ebo);
  glBindVertexArray(state.vao);

  glBindBuffer(GL_ARRAY_BUFFER, state.vbo);
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
  f32 offset = 0;
  for (i32 i = 0; i < RENDERER_MAX_INDEX; i += 6) {
    indices[i + 0] = 0 + offset;
    indices[i + 1] = 1 + offset;
    indices[i + 2] = 2 + offset;

    indices[i + 3] = 2 + offset;
    indices[i + 4] = 3 + offset;
    indices[i + 5] = 0 + offset;

    offset += 4;
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  for (i32 i = 0; i < RENDERER_MAX_TEXTURES; i++) {
    state.sampler[i] = i;
  }

  state.tex_white = texture_white_create();
  memset(state.textures, 0, sizeof(state.textures));
  state.textures[0] = &state.tex_white;
  
  state.tex_slot = 1;
  state.index_count = 0;

  camera_init();

  shader_send_int_array(&state.shader_, "u_image", RENDERER_MAX_TEXTURES, state.sampler);
  shader_send_mat4(&state.shader_, "u_proj", camera_update_projection(window_get_width(), window_get_height()));
  shader_send_mat4(&state.shader_, "u_view", camera_update_view());

  event_subscribe(EVENT_CODE_CAMERA_MOVED, &state, renderer_update_view);
  event_subscribe(EVENT_CODE_WINDOW_RESIZED, &state, renderer_update_projection);

  initialized = TRUE;
  VALLY_TRACE("Renderer system initialized");

  return TRUE;
}

void renderer_begin_batch() {
  if (!initialized) {
    return;
  }

  state.quad_buffer_ptr = state.quad_buffer;
}

void renderer_end_batch() {
  if (!initialized) {
    return;
  }

  glBindBuffer(GL_ARRAY_BUFFER, state.vbo);
  i32 size = (u8 *)state.quad_buffer_ptr - (u8 *)state.quad_buffer;
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, state.quad_buffer);
}

void renderer_flush() {
  if (!initialized) {
    return;
  }

  VALLY_TRACE("Renderer system: rendering - %d indices", state.index_count);

  for (i32 i = 0; i < state.tex_slot; i++) {
    texture_bind(i, state.textures[i]);
  }

  shader_attach(&state.shader_);
  glBindVertexArray(state.vao);

  glDrawElements(GL_TRIANGLES, state.index_count, GL_UNSIGNED_INT, NULL);

  state.index_count = 0;
  state.tex_slot = 1;
}

void renderer_terminate() {
  if (!initialized) {
    return;
  }

  glDeleteVertexArrays(1, &state.vao);
  glDeleteBuffers(1, &state.vbo);
  glDeleteBuffers(1, &state.ebo);

  initialized = FALSE;

  VALLY_TRACE("Renderer system terminated");
}

void renderer_clear_screen() {
  if (!initialized) {
    return;
  }

  // clear screen
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // enable depth test
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_ALWAYS);

  // enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void renderer_draw_quad(texture *tex, vec2s pos) {
  if (!initialized) {
    return;
  }

  if (state.index_count >= RENDERER_MAX_INDEX || state.tex_slot > RENDERER_MAX_TEXTURES - 1) {
    renderer_end_batch();
    renderer_flush();
    renderer_begin_batch();
  }

  vec4s color = GLMS_VEC4_ONE;
  
  f32 tex_id = 0.0f;
  for (i32 i = 1; i < state.tex_slot; i++) {
    if (state.textures[i] == tex) {
      tex_id = (float)i;
      break;
    }
  }

  if (tex_id == 0.0f) {
    tex_id = (float)state.tex_slot;
    state.textures[state.tex_slot] = tex;
    state.tex_slot++;
  }

  state.quad_buffer_ptr->pos[0] = pos.x;
  state.quad_buffer_ptr->pos[1] = pos.y;
  state.quad_buffer_ptr->color[0] = color.x;
  state.quad_buffer_ptr->color[1] = color.y;
  state.quad_buffer_ptr->color[2] = color.z;
  state.quad_buffer_ptr->color[3] = color.w;
  state.quad_buffer_ptr->uv[0] = 0.0f;
  state.quad_buffer_ptr->uv[1] = 0.0f;
  state.quad_buffer_ptr->tex_id = tex_id;
  state.quad_buffer_ptr++;

  state.quad_buffer_ptr->pos[0] = pos.x + 64.0f;
  state.quad_buffer_ptr->pos[1] = pos.y;
  state.quad_buffer_ptr->color[0] = color.x;
  state.quad_buffer_ptr->color[1] = color.y;
  state.quad_buffer_ptr->color[2] = color.z;
  state.quad_buffer_ptr->color[3] = color.w;
  state.quad_buffer_ptr->uv[0] = 1.0f;
  state.quad_buffer_ptr->uv[1] = 0.0f;
  state.quad_buffer_ptr->tex_id = tex_id;
  state.quad_buffer_ptr++;

  state.quad_buffer_ptr->pos[0] = pos.x + 64.0f;
  state.quad_buffer_ptr->pos[1] = pos.y + 64.0f;
  state.quad_buffer_ptr->color[0] = color.x;
  state.quad_buffer_ptr->color[1] = color.y;
  state.quad_buffer_ptr->color[2] = color.z;
  state.quad_buffer_ptr->color[3] = color.w;
  state.quad_buffer_ptr->uv[0] = 1.0f;
  state.quad_buffer_ptr->uv[1] = 1.0f;
  state.quad_buffer_ptr->tex_id = tex_id;
  state.quad_buffer_ptr++;

  state.quad_buffer_ptr->pos[0] = pos.x;
  state.quad_buffer_ptr->pos[1] = pos.y + 64.0f;
  state.quad_buffer_ptr->color[0] = color.x;
  state.quad_buffer_ptr->color[1] = color.y;
  state.quad_buffer_ptr->color[2] = color.z;
  state.quad_buffer_ptr->color[3] = color.w;
  state.quad_buffer_ptr->uv[0] = 0.0f;
  state.quad_buffer_ptr->uv[1] = 1.0f;
  state.quad_buffer_ptr->tex_id = tex_id;
  state.quad_buffer_ptr++;

  state.index_count += 6;
}