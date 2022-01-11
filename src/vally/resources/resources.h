#ifndef VALLY_RESOURCES_RESOURCES_H_
#define VALLY_RESOURCES_RESOURCES_H_

#include <vally/resources/resource_types.h>

b8 resources_init();
void resources_add(void *data, destructor_fun destructor);
void resources_terminate();

#endif // !VALLY_RESOURCES_RESOURCES_H_