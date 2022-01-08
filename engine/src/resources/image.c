#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "resources.h"
#include "core/logger.h"

image *load_image(const char *path) {
  image *img = (image *)malloc(sizeof(image));
  img->buffer = stbi_load(path, &img->width, &img->height, &img->channels, STBI_rgb_alpha);
  if (!img->buffer) {
    VALLY_ERROR("Could not load image at \"%s\"!", path);
    return NULL;
  }

  resources_add(img, unload_image);
  return img;
}

void unload_image(void *img) {
  image *i = (image *)img;
  stbi_image_free(i->buffer);
}