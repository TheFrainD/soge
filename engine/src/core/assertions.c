#include "assertions.h"

#include "logger.h"

void report_assert_fail(const char *expression, const char *message, const char *file, i32 line) {
  VALLY_FATAL("Assertion failure: (%s), %s -- %s:%d", expression, message, file, line);
}