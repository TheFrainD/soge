/*********************************************************************
 * camera.h                                                          *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_CAMERA_H_
#define VALLY_CAMERA_H_

#include <vally/config.h>
#include <vally/math/math.h>

b8 camera_init();
VALLY_API void camera_translate(vector2f translation);

#endif // VALLY_CAMERA_H_