#ifndef VALLY_CORE_LOGGER_H_
#define VALLY_CORE_LOGGER_H_

#include <log.h>

#include <vally/config.h>

#ifdef _DEBUG
#define LOG_LEVEL 5
#else
#define LOG_LEVEL 2
#endif

b8 logger_init();

#define VALLY_FATAL(MSG, ...) log_fatal(MSG, ##__VA_ARGS__)

#define VALLY_ERROR(MSG, ...) log_error(MSG, ##__VA_ARGS__)

#if LOG_LEVEL >= 2
#define VALLY_WARN(MSG, ...) log_warn(MSG, ##__VA_ARGS__)
#else
#define VALLY_WARN(MSG, ...)
#endif // LOG_LEVEL

#if LOG_LEVEL >= 3
#define VALLY_INFO(MSG, ...) log_info(MSG, ##__VA_ARGS__)
#else
#define VALLY_INFO(MSG, ...)
#endif // LOG_LEVEL

#if LOG_LEVEL >= 4
#define VALLY_DEBUG(MSG, ...) log_debug(MSG, ##__VA_ARGS__)
#else
#define VALLY_DEBUG(MSG, ...)
#endif // LOG_LEVEL

#if LOG_LEVEL >= 5
#define VALLY_TRACE(MSG, ...) log_trace(MSG, ##__VA_ARGS__)
#else
#define VALLY_TRACE(MSG, ...)
#endif // LOG_LEVEL

#endif // !VALLY_CORE_LOGGER_H_