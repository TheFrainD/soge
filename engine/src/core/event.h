#ifndef VALLY_CORE_EVENT_H_
#define VALLY_CORE_EVENT_H_

#include "defines.h"

typedef struct {
  // 128 bytes of data
  union {
    i64 i64[2];
    u64 u64[2];
    f64 f64[2];

    i32 i32[4];
    u32 u32[4];
    f32 f32[4];

    i16 i16[8];
    u16 u16[8];

    i8 i8[8];
    u8 u8[8];

    char c[16];
  } data;
} event_context;

typedef b8 (*on_event_fun)(u16 code, void *sender, void *listener, event_context context);

b8 event_init();
void event_terminate();

VALLY_DLL b8 event_subscribe(u16 code, void *listener, on_event_fun callback);

VALLY_DLL b8 event_unsubscribe(u16 code, void *listener, on_event_fun callback);

VALLY_DLL b8 event_publish(u16 code, void *sender, event_context context);

typedef enum {
  EVENT_CODE_APP_QUIT,
  EVENT_CODE_KEY_PRESSED,
  EVENT_CODE_RELEASED,
  EVENT_CODE_MOUSE_BUTTON_PRESSED,
  EVENT_CODE_MOUSE_BUTTON_RELEASED,
  EVENT_CODE_MOUSE_MOVED,
  EVENT_CODE_MOUSE_WHEEL,
  EVENT_CODE_WINDOW_RESIZED,

  MAX_EVENT_CODE = 255
} engine_event_code;

#endif  // !VALLY_CORE_EVENT_H_