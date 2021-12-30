#ifndef SOGE_CORE_ENGINE_H_
#define SOGE_CORE_ENGINE_H_

#include "defines.h"

SAPI b8 engine_create(i16 width, i16 height, const char *title);

SAPI b8 engine_run();

#endif // !SOGE_CORE_ENGINE_H_