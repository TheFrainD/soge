//===================================================================
// engine.h
//
// Copyright (c) 2022 Dmytro Zykov
//
// This file is a part of the vally project, and may only be used,
// modified and distributed under the terms of the MIT License, 
// LICENSE.md. By continuing to use, modify and distribute this file
// you inidicate that you have read the license and accept it fully.
//===================================================================

#ifndef VALLY_ENGINE_H_
#define VALLY_ENGINE_H_

#include <vally/config.h>

/*!
 *  \brief Client API function pointer
 *  
 *  Called after engine is initialized, before main loop
 * 
 */
typedef b8 (*engine_start)(void);

/*!
 *  \brief Client API function pointer
 *  
 *  Called inside main loop before rendering phase
 * 
 */
typedef b8 (*engine_update)(f32 delta_time);

/*!
 *  \brief Client API function pointer
 *  
 *  Called inside main loop in rendering phase
 * 
 */
typedef b8 (*engine_render)(f32 delta_time);

/*! 
 *  \brief Initializes the vally engine
 *  
 *  This function initializes the vally engine. Must be called before
 *  any other vally function calls.
 *  
 *  \param width Target window width
 *  \param height Target window height
 *  \param title Target window title
 *  
 *  \return TRUE - if success, FALSE - in case of fatal errors
 * 
 */
VALLY_API b8 engine_create(i16 width, i16 height, const char *title);

/*! 
 *  \brief Runs the vally engine
 *  
 *  This function runs the vally engine.
 *  
 *  \param start Function that will be called before main loop
 *  \param update Function that will be called before rendering
 *  \param render Function that will be called in rendering
 *  
 *  \return TRUE - if success, FALSE - in case of fatal errors
 * 
 */
VALLY_API b8 engine_run(engine_start start, engine_update update, engine_render render);

#endif // VALLY_ENGINE_H_