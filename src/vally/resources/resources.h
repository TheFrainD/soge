#ifndef VALLY_RESOURCES_H_
#define VALLY_RESOURCES_H_

#include <vally/config.h>

typedef void (*destructor_fun)(void *);

typedef struct {
  void *data;
  destructor_fun destructor;
} resource;

b8 resources_init();
void resources_add(void *data, destructor_fun destructor);
void resources_terminate();

#endif // VALLY_RESOURCES_H_