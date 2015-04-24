#include <stdlib.h>
#include <stdbool.h>
#include "xopt.h"

#define EXTRAS_INIT 10

struct xoptContext {
  xoptOption *options;
  long flags;
  const char *name;
  size_t extrasCapac;
  const char **extras;
};

xoptContext* xopt_context(const char *name, xoptOption *options, long flags,
    const char **err) {
  xoptContext* ctx;
  *err = 0;

  ctx = malloc(sizeof(xoptContext));
  if (ctx == 0) {
    ctx = 0;
    *err = "could not allocate context";
  } else {
    ctx->options = options;
    ctx->flags = flags;
    ctx->name = name;
    ctx->extrasCapac = EXTRAS_INIT;
    ctx->extras = malloc(sizeof(*(ctx->extras)) * EXTRAS_INIT);
  }

  return ctx;
}
