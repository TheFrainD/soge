#include <vally/resources/image.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <vally/resources/resources.h>
#include <vally/core/logger.h>

image *image_load(const char *path) {
  image *img = (image *)malloc(sizeof(image));
  img->buffer = stbi_load(path, &img->width, &img->height, &img->channels, STBI_rgb_alpha);
  if (!img->buffer) {
    LOG_ERROR("Could not load image at \"%s\"!", path);
    return NULL;
  }

  resources_add(img, image_unload);
  return img;
}

void image_unload(image *img) {
  stbi_image_free(img->buffer);
}