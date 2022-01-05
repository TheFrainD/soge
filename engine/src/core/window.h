#ifndef VALLY_CORE_WINDOW_H_
#define VALLY_CORE_WINDOW_H_

#include "defines.h"

b8 window_create(i32 width, i32 height, const char* title);

b8 window_poll_events();

void window_swap_buffers();

void window_terminate();

#endif // !VALLY_CORE_WINDOW_H_