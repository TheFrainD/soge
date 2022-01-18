/*********************************************************************
 * texture.h                                                         *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_TEXTURE_H_
#define VALLY_TEXTURE_H_

#include <vally/config.h>
#include <vally/resources/image.h>

/**
 * @brief Texture struct.
 * 
 * Contains OpenGL texture and its dimensions.
 * 
 * INFO: Recommended declaring a pointer.
 */
typedef struct {
  u32 id;
  i32 width;
  i32 height;
} texture;

/**
 * @brief Creates new texture from image.
 * 
 * @param img image source
 * @return textureS
 */
VALLY_API texture *texture_create(image *image);

// Creates white texture 1x1.
// Needed for colored quads "without texture".
texture *texture_white_create();

// Simple destructor
void texture_destroy(texture *texture);

// Binds OpenGL texture to given texture slot
void texture_bind(u32 unit, texture *texture);

// Unbinds texture (Actually, it's not used, but maybe needed in the future)
void texture_unbind();

#endif // VALLY_TEXTURE_H_