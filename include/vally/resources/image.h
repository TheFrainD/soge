/*********************************************************************
 * image.h                                                           *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_IMAGE_H_
#define VALLY_IMAGE_H_

#include <vally/config.h>

typedef struct {
  u8 *buffer;
  i32 width;
  i32 height;
  i32 channels;
} image;

VALLY_API image *image_load(const char *path);

void image_unload(image *img);


#endif // VALLY_IMAGE_H_