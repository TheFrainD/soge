/*********************************************************************
 * window.c                                                          *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_WINDOW_H_
#define VALLY_WINDOW_H_

#include <vally/config.h>

b8 window_create(i32 width, i32 height, char* title);

b8 window_poll_events();

void window_swap_buffers();

void window_terminate();

void window_set_key_callback(void *callback);

void window_set_mouse_button_callback(void *callback);

void window_set_cursor_position_callback(void *callback);

i32 window_get_width();

i32 window_get_height();

#endif // VALLY_WINDOW_H_
