#ifndef VALLY_RENDERER_RENDERER_H_
#define VALLY_RENDERER_RENDERER_H_

#define RENDERER_MAX_QUADS 1000
#define RENDERER_MAX_VERTEX RENDERER_MAX_QUADS * 4
#define RENDERER_MAX_INDEX RENDERER_MAX_QUADS * 6
#define RENDERER_MAX_TEXTURES 16

#include <cglm/cglm.h>
#include <cglm/struct.h>

#include "defines.h"

#include "renderer/texture.h"

b8 renderer_init();
void renderer_terminate();

void renderer_clear_screen();
VALLY_DLL void renderer_draw_quad(texture *tex, vec2s pos);

void renderer_begin_batch();
void renderer_end_batch();
void renderer_flush();

#endif // !VALLY_RENDERER_RENDERER_H_