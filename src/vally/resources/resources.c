#include <vally/resources/resources.h>

#include <stdlib.h>

#include <cvec.h>

#include <vally/core/logger.h>
#include <vally/resources/resource_types.h>

typedef struct {
  cvec resources;
} resources_state;

static b8 initalized = FALSE;
static resources_state state;

b8 resources_init() {
  if (initalized) {
    return FALSE;
  }

  initalized = TRUE;
  state.resources = cvec_create(resource);

  VALLY_TRACE("Resource system initialized");
  return TRUE;
}

void resources_add(void *data, destructor_fun destructor) {
  if (!initalized) {
    return;
  }

  resource res;
  res.data = data;
  res.destructor = destructor;
  cvec_push_back(state.resources, res);
}

void resources_terminate() {
  if (!initalized) {
    return;
  } 

  for (int i = 0; i < cvec_size(state.resources); i++) {
    resource res = cvec_at(state.resources, i, resource);
    res.destructor(res.data);
  }

  VALLY_INFO("Resource system: %d objects destroyed", cvec_size(state.resources));
  cvec_destroy(state.resources);

  VALLY_TRACE("Resource system terminated");
}
