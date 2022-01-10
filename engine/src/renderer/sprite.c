#include "renderer/sprite.h"

#include <stdlib.h>

#include "core/logger.h"
#include "resources/resources.h"

static void sprite_spritesheet_destroy(spritesheet *sheet) {
  free(sheet->sprites);
}

sprite sprite_create(texture *tex) {
  sprite spr;

  spr.tex = tex;
  spr.size = vector2f_create((f32)tex->width, (f32)tex->height);
  spr.anim = SPRITE_STATIC_ANIMATION;
  
  spr.uv[0] = vector2f_create(0.0f, 0.0f);
  spr.uv[1] = vector2f_create(1.0f, 0.0f);
  spr.uv[2] = vector2f_create(1.0f, 1.0f);
  spr.uv[3] = vector2f_create(0.0f, 1.0f);

  return spr;
}

spritesheet *sprite_spritesheet_create(texture *tex, vector2f tiling) {
  spritesheet *sheet = (spritesheet *)malloc(sizeof(spritesheet));
  if (!sheet) {
    VALLY_ERROR("Coud not allocate memory for spritesheet!");
    return NULL;
  }

  sheet->tex = tex;
  sheet->tiling = tiling;

  i32 sprites_per_row = tex->width / tiling.x;
  i32 sprites_per_column = tex->height / tiling.y;
  i32 sprite_count = sprites_per_row * sprites_per_column;
  sheet->sprites = (sprite *)malloc(sizeof(sprite) * sprite_count);
  for (i32 i = 0; i < sprite_count; i++) {
    f32 tw = tiling.x / tex->width;
    f32 th = tiling.y / tex->height;
    f32 tx = (i % sprites_per_row) * tw;
    f32 ty = (i / sprites_per_row) * th;

    sprite spr = sprite_create(tex);
    spr.size = tiling;
    spr.uv[0] = vector2f_create(tx, ty);
    spr.uv[1] = vector2f_create(tx + tw, ty);
    spr.uv[2] = vector2f_create(tx + tw, ty + th);
    spr.uv[3] = vector2f_create(tx, ty + th);
    sheet->sprites[i] = spr;
  }

  resources_add(sheet, sprite_spritesheet_destroy);

  return sheet;
}

sprite sprite_spritesheet_get(spritesheet *sheet, i32 index) {
  return sheet->sprites[index];
}