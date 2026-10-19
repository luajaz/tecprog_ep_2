#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#define EXPECT(cond)                                                           \
  do {                                                                         \
    if (!(cond)) {                                                             \
      printf("  FALHOU: %s (%s:%d)\n", #cond, __FILE__, __LINE__);             \
      st = TEST_FAIL;                                                          \
    }                                                                          \
} while (0)

typedef enum { TEST_SUCCESS = 0, TEST_FAIL = 1 } test_status;

static inline bool double_compare(double a, double b, double tol) { return (fabs(a - b) <= tol) ? true : false;}

#endif
