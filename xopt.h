#ifndef XOPT_H__
#define XOPT_H__
#pragma once

#include <stdio.h>

struct xoptOption;

typedef void (*xoptCallback)(
    const char              *value,
    void                    *data,
    const struct xoptOption *option,
    const char              **err);

enum xoptOptionFlag {
  XOPT_TYPE_STRING          = 0x1,
  XOPT_TYPE_INT             = 0x2,
  XOPT_TYPE_LONG            = 0x4,
  XOPT_TYPE_FLOAT           = 0x8,
  XOPT_TYPE_DOUBLE          = 0x10,
  XOPT_TYPE_BOOL            = 0x20,

  XOPT_OPTIONAL             = 0x40,
  XOPT_SHOW_DEFAULT         = 0x80
};

enum xoptContextFlag {
  XOPT_CTX_KEEPFIRST        = 0x1,
  XOPT_CTX_POSIXMEHARDER    = 0x2
};

typedef struct xoptOption {
  const char                *longArg;
  const char                *shortArg;
  void                      *defaultVal;
  size_t                    offset;
  xoptCallback              callback;
  long                      options;
  const char                *argDescrip;
  const char                *descrip;
} xoptOption;

#define XOPT_NULLOPT {0, 0, 0, 0, 0, 0, 0}

typedef struct xoptContext xoptContext;

xoptContext*
xopt_context(
    const char              *name,
    xoptOption              *options,
    long                    flags,
    const char              **err);

/* XXX returns the number of extras */
int
xopt_parse(
    xoptContext             *ctx,
    int                     argc,
    const char              **argv,
    const char              **extra,
    const char              **err);

void
xopt_autohelp(
    FILE                    *stream,
    xoptContext             *ctx);

#endif
