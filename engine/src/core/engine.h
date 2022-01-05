#ifndef VALLY_CORE_ENGINE_H_
#define VALLY_CORE_ENGINE_H_

#include "defines.h"

typedef b8 (*engine_start)();
typedef b8 (*engine_update)(f32);
typedef b8 (*engine_render)(f32);

VALLY_DLL b8 engine_create(i16 width, i16 height, const char *title);

VALLY_DLL b8 engine_run(engine_start start, engine_update update, engine_render render);

#endif // !VALLY_CORE_ENGINE_H_