#include <vally/core/event.h>

#include <stdlib.h>
#include <string.h>

#include <cvec.h>

#include <vally/core/logger.h>

typedef struct {
  void *listener;
  on_event_fun callback;
} registered_event;

typedef struct {
  cvec events;
} event_code_entry;

#define MAX_MESSAGE_CODES 16384

typedef struct {
  event_code_entry registered[MAX_MESSAGE_CODES];
} event_system_state;

static b8 initialized = FALSE;
static event_system_state state;

b8 event_init() {
  if (initialized) {
    return TRUE;
  }

  memset(&state, 0, sizeof(state));
  initialized = TRUE;
  VALLY_TRACE("Event system initialized");

  return TRUE;
}

void event_terminate() {
  for (int i = 0; i < MAX_MESSAGE_CODES; i++) {
    if (state.registered[i].events != NULL) {
      cvec_destroy(state.registered[i].events);
      state.registered[i].events = NULL;
    }
  }
  VALLY_TRACE("Event system terminated");
}

b8 event_subscribe(u16 code, void *listener, on_event_fun callback) {
  if (!initialized) {
    return FALSE;
  }

  if (state.registered[code].events == NULL) {
    state.registered[code].events = cvec_create(registered_event);
  }

  u64 registered_count = cvec_size(state.registered[code].events);
  for (int i = 0; i < registered_count; i++) {
    if (cvec_at(state.registered[code].events, i, registered_event).listener == listener) {
      // TODO: warn
      return FALSE;
    }
  }

  registered_event event;
  event.listener = listener;
  event.callback = callback;
  cvec_push_back(state.registered[code].events, event);

  return TRUE;
}

b8 event_unsubscribe(u16 code, void *listener, on_event_fun callback) {
  if (!initialized) {
    return FALSE;
  }

  if (state.registered[code].events == NULL) {
    return FALSE;
  }

  u64 registered_count = cvec_size(state.registered[code].events);
  for (int i = 0; i < registered_count; i++) {
    registered_event event = cvec_at(state.registered[code].events, i, registered_event);
    if (event.listener == listener && event.callback == callback) {
      cvec_erase(state.registered[code].events, i);
      return TRUE;
    }
  }

  return FALSE;
}

b8 event_publish(u16 code, void *sender, event_context context) {
  if (!initialized) {
    return FALSE;
  }

  if (state.registered[code].events == NULL) {
    return FALSE;
  }

  u64 registered_count = cvec_size(state.registered[code].events);
  for (int i = 0; i < registered_count; i++) {
    registered_event event = cvec_at(state.registered[code].events, i, registered_event);
    if (event.callback(code, sender, event.listener, context)) {
      return TRUE;
    }
  }

  return FALSE;
}