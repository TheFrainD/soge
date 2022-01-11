#ifndef VALLY_RESOURCES_IMAGE_H_
#define VALLY_RESOURCES_IMAGE_H_

#include <vally/resources/resource_types.h>
#include <vally/config.h>

VALLY_API image *image_load(const char *path);

void image_unload(image *img);


#endif // !VALLY_RESOURCES_IMAGE_H_