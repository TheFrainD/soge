#ifndef SOGE_CORE_LOGGER_H_
#define SOGE_CORE_LOGGER_H_

#include <log/log.h>

#include "defines.h"

#ifdef _DEBUG
#define LOG_LEVEL 5
#else
#define LOG_LEVEL 2
#endif

b8 logger_init();

#define SOGE_FATAL(MSG, ...) log_fatal(MSG, ##__VA_ARGS__)

#define SOGE_ERROR(MSG, ...) log_error(MSG, ##__VA_ARGS__)

#if LOG_LEVEL >= 2
#define SOGE_WARN(MSG, ...) log_warn(MSG, ##__VA_ARGS__)
#else
#define SOGE_WARN(MSG, ...)
#endif // LOG_LEVEL

#if LOG_LEVEL >= 3
#define SOGE_INFO(MSG, ...) log_info(MSG, ##__VA_ARGS__)
#else
#define SOGE_INFO(MSG, ...)
#endif // LOG_LEVEL

#if LOG_LEVEL >= 4
#define SOGE_DEBUG(MSG, ...) log_debug(MSG, ##__VA_ARGS__)
#else
#define SOGE_DEBUG(MSG, ...)
#endif // LOG_LEVEL

#if LOG_LEVEL >= 5
#define SOGE_TRACE(MSG, ...) log_trace(MSG, ##__VA_ARGS__)
#else
#define SOGE_TRACE(MSG, ...)
#endif // LOG_LEVEL

#endif // !SOGE_CORE_LOGGER_H_