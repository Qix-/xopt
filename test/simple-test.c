#include <stdio.h>
#include "xopt.h"

xoptOption options[] = {
  XOPT_NULLOPTION
};

int main(void) {
  int result;
  const char *err;
  xoptContext *ctx;

  result = 0;
  err = 0;

  /* create context */
  ctx = xopt_context("xopt-test", options, XOPT_CTX_POSIXMEHARDER, &err);
  if (err) {
    fprintf(stderr, "Error: %s\n", err);
    result = 1;
    goto exit;
  }

  ((void)ctx);

exit:
  return result;
}
