#ifndef VALLY_RENDERER_TEXTURE_H_
#define VALLY_RENDERER_TEXTURE_H_

#include "defines.h"
#include "resources/image.h"

typedef struct {
  u32 id;
  i32 width;
  i32 height;
} texture;

texture texture_create(image *img);
texture texture_white_create();
void texture_destroy(void *tex);

void texture_bind(u32 unit, texture *tex);
void texture_unbind();

#endif // !VALLY_RENDERER_TEXTURE_H_