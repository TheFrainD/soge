#ifndef VALLY_RESOURCES_IMAGE_H_
#define VALLY_RESOURCES_IMAGE_H_

#include "resource_types.h"
#include "defines.h"

image *load_image(const char *path);

void unload_image(void *img);


#endif // !VALLY_RESOURCES_IMAGE_H_