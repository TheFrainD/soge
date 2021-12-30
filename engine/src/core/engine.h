#ifndef SOGE_CORE_ENGINE_H_
#define SOGE_CORE_ENGINE_H_

#include "defines.h"

typedef b8 (*engine_start)();
typedef b8 (*engine_update)(f32);
typedef b8 (*engine_render)(f32);

SAPI b8 engine_create(i16 width, i16 height, const char *title);

SAPI b8 engine_run(engine_start start, engine_update update, engine_render render);

#endif // !SOGE_CORE_ENGINE_H_