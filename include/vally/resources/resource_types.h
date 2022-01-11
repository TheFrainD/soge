#ifndef VALLY_RESOURCES_RECOURCE_TYPES_H_
#define VALLY_RESOURCES_RECOURCE_TYPES_H_

#include <vally/config.h>

typedef void (*destructor_fun)(void *);

typedef struct {
  i8 *buffer;
  i32 width;
  i32 height;
  i32 channels;
} image;

typedef struct {
  void *data;
  destructor_fun destructor;
} resource;

#endif // !VALLY_RESOURCES_RECOURCE_TYPES_H_
