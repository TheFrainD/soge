#ifndef VALLY_RENDERER_SPRITE_H_
#define VALLY_RENDERER_SPRITE_H_

#include "defines.h"

#include "renderer/texture.h"
#include "math/vmath.h"

typedef struct {
  b8 is_static;
  i32 first_frame;
  i32 last_frame;
  f32 framerate;
  i32 current_frame;
  f32 current_time;
} animation;

typedef struct {
  texture *tex;
  vector2f size;
  vector2f uv[4];
  animation anim;
} sprite;

typedef struct {
  sprite *sprites;
  texture *tex;
  vector2f tiling;
} spritesheet;

VALLY_DLL sprite sprite_create(texture *tex);

VALLY_DLL spritesheet *sprite_spritesheet_create(texture *tex, vector2f tiling);

VALLY_DLL sprite sprite_spritesheet_get(spritesheet *sheet, i32 index);

#define SPRITE_STATIC_ANIMATION ((animation){TRUE, 0, 0, 0.0f, 0, 0.0f})

#endif // !VALLY_RENDERER_SPRITE_H_