#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "../xopt.h"

typedef struct {
	int someInt;
	float someFloat;
	double someDouble;
	bool help;
} SimpleConfig;

xoptOption options[] = {
	{
		"some-int",
		'i',
		offsetof(SimpleConfig, someInt),
		0,
		XOPT_TYPE_INT,
		"n",
		"Some integer value. Can set to whatever number you like."
	},
	{
		"some-float",
		'f',
		offsetof(SimpleConfig, someFloat),
		0,
		XOPT_TYPE_FLOAT,
		"n",
		"Some float value."
	},
	{
		"some-double",
		'd',
		offsetof(SimpleConfig, someDouble),
		0,
		XOPT_TYPE_DOUBLE,
		"n",
		"Some double value."
	},
	{
		"help",
		'?',
		offsetof(SimpleConfig, help),
		0,
		XOPT_TYPE_BOOL,
		0,
		"Shows this help message"
	},
	XOPT_NULLOPTION
};

int main(int argc, const char **argv) {
	int result;
	const char *err;
	xoptContext *ctx;
	SimpleConfig config;
	const char **extras = 0;
	const char **extrasPtr = 0;
	int extraCount;

	result = 0;
	err = 0;

	/* show arguments */
	fputs("args:", stderr);
	for (int i = 1; i < argc; i++) {
		fprintf(stderr, " «%s»", argv[i]);
	}
	fputs("\n\n", stderr);

	/* setup defaults */
	config.someInt = 0;
	config.someDouble = 0.0;
	config.help = 0;

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

	/* help? */
	if (config.help) {
		xoptAutohelpOptions opts;
		opts.usage = "usage: simple-test [options] [extras...]";
		opts.prefix = "A simple demonstration of the XOpt options parser library.";
		opts.suffix = "End argument list.";
		opts.spacer = 10;

		xopt_autohelp(ctx, stderr, &opts, &err);
		goto exit;
	}

	/* print */
#define P(field, delim) fprintf(stderr, #field ":\t%" #delim "\n",              \
		config.field)

	P(someInt, d);
	P(someFloat, f);
	P(someDouble, f);
	P(help, d);

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
