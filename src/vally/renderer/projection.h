/*********************************************************************
 * projection.h                                                      *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_PROJECTION_H_
#define VALLY_PROJECTION_H_

#include <vally/config.h>

#include <cglm/cglm.h>
#include <cglm/struct.h>

mat4s camera_update_projection(i32 width, i32 height);
mat4s camera_update_view();
mat4s camera_get_projection();
mat4s camera_get_view();

#endif // VALLY_PROJECTION_H_