/**
 * XOpt - command line parsing library
 *
 * Copyright (c) 2015 JD Ballard.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include "xopt.h"

#define EXTRAS_INIT 10
#define ERRBUF_SIZE 1024*4

static char errbuf[ERRBUF_SIZE];

struct xoptContext {
  xoptOption *options;
  long flags;
  const char *name;
};

int rpl_vsnprintf(char *, size_t, const char *, va_list);

static void _xopt_set_err(const char **err, const char *const fmt, ...);
static bool _xopt_parse_arg(xoptContext *ctx, int argc, const char **argv,
    int argi, void *data, const char **err);
static void _xopt_assert_increment(const char ***extras, int extrasCount,
    size_t *extrasCapac, const char **err);

xoptContext* xopt_context(const char *name, xoptOption *options, long flags,
    const char **err) {
  xoptContext* ctx;
  *err = 0;

  ctx = malloc(sizeof(xoptContext));
  if (!ctx) {
    ctx = 0;
    _xopt_set_err(err, "could not allocate context");
  } else {
    ctx->options = options;
    ctx->flags = flags;
    ctx->name = name;
  }

  return ctx;
}

int xopt_parse(xoptContext *ctx, int argc, const char **argv, void* data,
    const char ***inextras, const char **err) {
  int argi;
  int extrasCount;
  size_t extrasCapac;
  const char **extras;
  bool parseResult;

  *err = 0;
  argi = 0;
  extrasCount = 0;
  extrasCapac = EXTRAS_INIT;
  extras = malloc(sizeof(*extras) * EXTRAS_INIT);

  if (!extras) {
    _xopt_set_err(err, "could not allocate extras array");
    goto end;
  }

  if (!(ctx->flags & XOPT_CTX_KEEPFIRST)) {
    ++argi;
  }

  for (; argi < argc; argi++) {
    parseResult = _xopt_parse_arg(ctx, argc, argv, argi, data, err);
    if (*err) {
      break;
    }

    if (parseResult) {
      _xopt_assert_increment(&extras, extrasCount, &extrasCapac, err);
      if (*err) {
        break;
      }
      extras[extrasCount++] = argv[argi];
    } else {
      if ((ctx->flags & XOPT_CTX_POSIXMEHARDER) && extrasCount) {
        _xopt_set_err(err, "options cannot be specified after arguments: %s",
            argv[argi]);
        break;
      }
    }
  }

end:
  if (*err) {
    if (extras) {
      free(extras);
    }
    *inextras = 0;
    return 0;
  } else {
    *inextras = extras;
    return extrasCount;
  }
}

static void _xopt_set_err(const char **err, const char *const fmt, ...) {
  va_list list;
  va_start(list, fmt);
  rpl_vsnprintf(&errbuf[0], ERRBUF_SIZE, fmt, list);
  va_end(list);
  *err = &errbuf[0];
}

static bool _xopt_parse_arg(xoptContext *ctx, int argc, const char **argv,
    int argi, void *data, const char **err) {
  *err = 0;

  ((void)argc);
  ((void)data);
  fprintf(stderr, "%d: %s <%s>\n", argi, argv[argi], ctx->name);
  return true;
}

static void _xopt_assert_increment(const char ***extras, int extrasCount,
    size_t *extrasCapac, const char **err) {
  if ((size_t) extrasCount == *extrasCapac) {
    *extrasCapac += EXTRAS_INIT;
    *extras = realloc(*extras, *extrasCapac);
    if (!*extras) {
      _xopt_set_err(err, "could not realloc arguments array");
    }
  }
}
