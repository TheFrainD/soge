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

#pragma once

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