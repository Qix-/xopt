#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "xopt.h"

typedef struct {
  int someInt;
} SimpleConfig;

xoptOption options[] = {
  {
    "some-int",
    'i',
    offsetof(SimpleConfig, someInt),
    0,
    XOPT_TYPE_INT | XOPT_SHOW_DEFAULT,
    "n",
    "Some integer value. Can set to whatever number you like."
  },
  XOPT_NULLOPTION
};

int main(int argc, const char **argv) {
  int result;
  const char *err;
  xoptContext *ctx;
  SimpleConfig config;
  const char **extras;
  const char **extrasPtr;
  int extraCount;

  result = 0;
  err = 0;

  /* setup defaults */
  config.someInt = 0;

  /* create context */
  ctx = xopt_context("xopt-test", options,
      XOPT_CTX_POSIXMEHARDER | XOPT_CTX_STRICT, &err);
  if (err) {
    fprintf(stderr, "Error: %s\n", err);
    result = 1;
    goto exit;
  }

  /* parse */
  extraCount = xopt_parse(ctx, argc, argv, &config, &extras, &err);
  if (err) {
    fprintf(stderr, "Error: %s\n", err);
    result = 2;
    goto exit;
  }

  /* print */
#define P(field, delim) fprintf(stderr, #field ":\t%" #delim "\n",              \
    config.field)

  P(someInt, d);

  fprintf(stderr, "\nextra count: %d\n", extraCount);
  extrasPtr = extras;
  while (extraCount--) {
    fprintf(stderr, "- %s\n", *extrasPtr++);
  }

#undef P

exit:
  if (extras) free(extras); /* DO NOT free individual strings */
  if (ctx) free(ctx);       /*   they point to argv strings   */
  return result;
}
