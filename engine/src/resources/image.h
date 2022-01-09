#ifndef VALLY_RESOURCES_IMAGE_H_
#define VALLY_RESOURCES_IMAGE_H_

#include "resource_types.h"
#include "defines.h"

image *image_load(const char *path);

void image_unload(image *img);


#endif // !VALLY_RESOURCES_IMAGE_H_