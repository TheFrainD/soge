#ifndef VALLY_RENDERER_RENDERER_H_
#define VALLY_RENDERER_RENDERER_H_

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