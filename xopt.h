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
#ifndef XOPT_H__
#define XOPT_H__
#pragma once

#include <stdio.h>
#include <stdbool.h>

struct xoptOption;

#ifndef offsetof
#	define offsetof(T, member) (size_t)(&(((T*)0)->member))
#endif

/**
 * Callback type for handling values.
 *  Called when a command line argument has been
 *  processed.
 */
typedef void (*xoptCallback)(
	const char              *value,         /* string cmd line option */
	void                    *data,          /* custom data structure */
	const struct xoptOption *option,        /* detected option */
	bool                    longArg,        /* true if the long-arg version
	                                           was used */
	const char              **err);         /* err output */

enum xoptOptionFlag {
	XOPT_TYPE_STRING          = 0x1,        /* const char* type */
	XOPT_TYPE_INT             = 0x2,        /* int type */
	XOPT_TYPE_LONG            = 0x4,        /* long type */
	XOPT_TYPE_FLOAT           = 0x8,        /* float type */
	XOPT_TYPE_DOUBLE          = 0x10,       /* double type */
	XOPT_TYPE_BOOL            = 0x20,       /* boolean (int) type */

	XOPT_OPTIONAL             = 0x40        /* whether the argument value is
	                                           optional */
};

enum xoptContextFlag {
	XOPT_CTX_KEEPFIRST        = 0x1,        /* don't ignore argv[0] */
	XOPT_CTX_POSIXMEHARDER    = 0x2,        /* options cannot come after
	                                           extra arguments */
	XOPT_CTX_NOCONDENSE       = 0x4,        /* don't allow short args to be
	                                           condensed (i.e. `ls -laF') */
	XOPT_CTX_SLOPPYSHORTS     = 0x8 | 0x4,  /* allow short arg values to be
	                                           directly after the character
	                                           (implies NOCONDENSE) */
	XOPT_CTX_STRICT           = 0x10        /* fails on invalid arguments */
};

typedef struct xoptOption {
	const char                *longArg;     /* --long-arg-name, or 0 for short
	                                           arg only */
	const char                shortArg;     /* -s hort arg character, or '\0'
	                                           for long arg only */
	size_t                    offset;       /* offsetof(type, property) for
	                                           automatic configuration handler */
	xoptCallback              callback;     /* callback for resolved option
	                                           handling */
	long                      options;      /* xoptOptionFlag options */
	const char                *argDescrip;  /* --argument=argDescrip (autohelp) */
	const char                *descrip;     /* argument explanation (autohelp) */
} xoptOption;

/* option list terminator */
#define XOPT_NULLOPTION {0, 0, 0, 0, 0, 0, 0}

typedef struct xoptContext xoptContext;

typedef struct xoptAutohelpOptions {
	const char                *usage;       /* usage string, or null */
	const char                *prefix;      /* printed before options, or null */
	const char                *suffix;      /* printed after options, or null */
	size_t                    spacer;       /* number of spaces between option and
	                                           description */
} xoptAutohelpOptions;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates an XOpt context to be used with
 * subsequent calls to XOpt functions
 */
xoptContext*
xopt_context(
	const char              *name,        /* name of the argument set (usually
	                                         name of the cli binary file/cmd */
	xoptOption              *options,     /* list of xoptOption objects,
	                                         terminated with XOPT_NULLOPTION */
	long                    flags,        /* xoptContextFlag flags */
	const char              **err);       /* pointer to a const char* that
	                                         receives an err should one occur -
	                                         set to 0 if command completed
	                                         successfully */

/**
 * Parses the command line of a program
 * and returns the number of non-options
 * returned to the `extras' pointer (see
 * below)
 */
int
xopt_parse(
	xoptContext             *ctx,         /* previously created XOpt context */
	int                     argc,         /* argc, from int main() */
	const char              **argv,       /* argv, from int main() */
	void                    *data,        /* a custom data object whos type
	                                         corresponds to `.offset' values
	                                         specified in the options list;
	                                         populated with values interpreted
	                                         from the command line */
	const char              ***extras,    /* receives a list of extra non-option
	                                         arguments (i.e. files, subcommands,
	                                         etc.) - length of which is returned
	                                         by the function call */
	const char              **err);       /* pointer to a const char* that
	                                         receives an err should one occur -
	                                         set to 0 if command completed
	                                         successfully */

/**
 * Generates and prints a help message
 * and prints it to a FILE stream.
 * If `defaults' is supplied, uses
 * offsets (values) defined by the options
 * list to show default options
 */
void
xopt_autohelp(
	xoptContext             *ctx,         /* previously created XOpt context */
	FILE                    *stream,      /* a stream to print to - if 0,
	                                         defaults to `stderr'. */
	xoptAutohelpOptions     *options,     /* configuration options to tailor
	                                         autohelp output */
	const char              **err);       /* pointer to a const char* that
	                                         receives an err should one occur -
	                                         set to 0 if command completed
	                                         successfully */

#ifdef __cplusplus
}
#endif
#endif
