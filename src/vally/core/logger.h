/*********************************************************************
 * logger.c                                                          *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_LOGGER_H_
#define VALLY_LOGGER_H_

#include <log.h>

#include <vally/config.h>

#ifdef VALLY_DEBUG
#define LOG_LEVEL 5
#else
#define LOG_LEVEL 2
#endif

b8 logger_init();

#define LOG_FATAL(MSG, ...) log_fatal(MSG, ##__VA_ARGS__)

#define LOG_ERROR(MSG, ...) log_error(MSG, ##__VA_ARGS__)

#if LOG_LEVEL >= 2
#define LOG_WARN(MSG, ...) log_warn(MSG, ##__VA_ARGS__)
#else
#define LOG_WARN(MSG, ...)
#endif // LOG_LEVEL

#if LOG_LEVEL >= 3
#define LOG_INFO(MSG, ...) log_info(MSG, ##__VA_ARGS__)
#else
#define LOG_INFO(MSG, ...)
#endif // LOG_LEVEL

#if LOG_LEVEL >= 4
#define LOG_DEBUG(MSG, ...) log_debug(MSG, ##__VA_ARGS__)
#else
#define LOG_DEBUG(MSG, ...)
#endif // LOG_LEVEL

#if LOG_LEVEL >= 5
#define LOG_TRACE(MSG, ...) log_trace(MSG, ##__VA_ARGS__)
#else
#define LOG_TRACE(MSG, ...)
#endif // LOG_LEVEL

#endif // VALLY_LOGGER_H_