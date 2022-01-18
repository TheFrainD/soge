/*********************************************************************
 * renderer.h                                                        *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_RENDERER_H_
#define VALLY_RENDERER_H_

#define RENDERER_MAX_QUADS 1000
#define RENDERER_MAX_VERTEX RENDERER_MAX_QUADS * 4
#define RENDERER_MAX_INDEX RENDERER_MAX_QUADS * 6
#define RENDERER_MAX_TEXTURES 16

#include <vally/config.h>

#include <vally/renderer/texture.h>
#include <vally/ecs/ecs.h>
#include <vally/math/math.h>

b8 renderer_init();
void renderer_terminate();

void renderer_clear_screen();

void renderer_draw(spriterenderer *sprite);

void renderer_begin_batch();
void renderer_end_batch();
void renderer_flush();

#endif // VALLY_RENDERER_H_