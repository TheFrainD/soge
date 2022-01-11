//================================================================================
// Vally 0.1indev
//--------------------------------------------------------------------------------
// Copyright (c) 2022 Dmytro Zykov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//=================================================================================

#include <vally/renderer/texture.h>

#include <stdlib.h>

#include <glad/glad.h>

#include <vally/core/logger.h>
#include <vally/resources/resources.h>

texture *texture_create(image *image) {
  texture *_texture = (texture *)malloc(sizeof(texture));
  if (!_texture) {
    VALLY_ERROR("Could not create texture");
  }

  // Generate OpenGL Texture
  glGenTextures(1, &_texture->id);
  glBindTexture(GL_TEXTURE_2D, _texture->id);

  // Configure texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  _texture->width = image->width;
  _texture->height = image->height;  // Binding image to the texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _texture->width, _texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->buffer);

  glBindTexture(GL_TEXTURE_2D, 0);

  resources_add(_texture, texture_destroy);

  return _texture;
}

texture *texture_white_create() {
  texture *_texture = (texture *)malloc(sizeof(texture));
  if (!_texture) {
    VALLY_ERROR("Could not create texture");
  }
  _texture->width = 1;
  _texture->height = 1;

  // generate white texture
  glGenTextures(1, &_texture->id);
  glBindTexture(GL_TEXTURE_2D, _texture->id);
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  u32 color = 0xffffffff; // white color
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);
  glBindTexture(GL_TEXTURE_2D, 0);

  return _texture;
}

void texture_destroy(texture *texture) {
  glDeleteTextures(1, &texture->id);
  free(texture);
}

void texture_bind(u32 unit, texture *texture) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, texture->id);
}

void texture_unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}