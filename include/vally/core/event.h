//===================================================================
// event.h
//
// Copyright (c) 2022 Dmytro Zykov
//
// This file is a part of the vally project, and may only be used,
// modified and distributed under the terms of the MIT License, 
// LICENSE.md. By continuing to use, modify and distribute this file
// you inidicate that you have read the license and accept it fully.
//===================================================================

#ifndef VALLY_EVENT_H_
#define VALLY_EVENT_H_

#include <vally/config.h>

/*!
 *  \brief Context send alongside the event
 * 
 */
typedef struct {
  /*!
   *  \brief Stores 128 bytes of date
   * 
   */
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

/*!
 *  \brief Pointer to event function
 * 
 */
typedef b8 (*on_event_fun)(u16 code, void *sender, void *listener, event_context context);

b8 event_init();
void event_terminate();

/*!
 *  \brief Subscribes for certain event types
 *  
 *  Executes the callback function when event is published
 *  
 *  \param code Event code
 *  \param listener Object that subscribes for an event
 *  \param callback Event callback function
 *  
 *  \return TRUE - if success, FALSE - in case of fatal errors
 * 
 */
VALLY_API b8 event_subscribe(u16 code, void *listener, on_event_fun callback);

/*!
 *  \brief Unsubscribes from certain event types
 *  
 *  Stops executing the callback function when event is published
 *  
 *  \param code Event code
 *  \param listener Object that unsubscribes from an event
 *  \param callback Event callback function
 *  
 *  \return TRUE - if success, FALSE - in case of fatal errors
 * 
 */
VALLY_API b8 event_unsubscribe(u16 code, void *listener, on_event_fun callback);

/*!
 *  \brief Publishes event of certain type
 *  
 *  \param code Event code
 *  \param sender Object that published the event
 *  \param context Context information sent alongside the event
 *  
 *  \return TRUE - if success, FALSE - in case of fatal errors 
 * 
 */
VALLY_API b8 event_publish(u16 code, void *sender, event_context context);

/*!
 *  \brief Event type codes
 *  
 *  User defined event codes must have code larger then 255
 *  
 */
typedef enum {
  EVENT_CODE_APP_QUIT,
  EVENT_CODE_KEY_PRESSED,
  EVENT_CODE_KEY_RELEASED,
  EVENT_CODE_MOUSE_BUTTON_PRESSED,
  EVENT_CODE_MOUSE_BUTTON_RELEASED,
  EVENT_CODE_MOUSE_MOVED,
  EVENT_CODE_MOUSE_WHEEL,
  EVENT_CODE_WINDOW_RESIZED,
  EVENT_CODE_CAMERA_MOVED,

  MAX_EVENT_CODE = 255
} engine_event_code;

#endif // VALLY_EVENT_H_