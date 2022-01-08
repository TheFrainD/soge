#include "texture.h"

#include <glad/glad.h>

#include "resources/resources.h"

texture texture_create(image *img) {
  texture tex;

  glGenTextures(1, &tex.id);
  glBindTexture(GL_TEXTURE_2D, tex.id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  tex.width = img->width;
  tex.height = img->height;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->buffer);

  glBindTexture(GL_TEXTURE_2D, 0);

  resources_add(&tex, texture_destroy);

  return tex;
}

texture texture_white_create() {
  texture tex;
  tex.width = 1;
  tex.height = 1;

  // generate white texture
  glGenTextures(1, &tex.id);
  glBindTexture(GL_TEXTURE_2D, tex.id);
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  u32 color = 0xffffffff;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);
  glBindTexture(GL_TEXTURE_2D, 0);

  return tex;
}

void texture_destroy(void *tex) {
  glDeleteTextures(1, ((texture *)tex)->id);
}

void texture_bind(u32 unit, texture *tex) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, tex->id);
}

void texture_unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}