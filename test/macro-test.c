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
	int exit_code = 1;
	const char *err = NULL;
	SimpleConfig config;
	const char **extras = NULL;
	const char **extrasPtr = NULL;
	int extraCount = 0;

	/* setup defaults */
	config.someInt = 0;
	config.someDouble = 0.0f;
	config.someDouble = 0.0;
	config.help = 0;

	XOPT_SIMPLE_PARSE(
		argv[0],
		&options[0], &config,
		argc, argv,
		&extraCount, &extras,
		&err,
		stderr,
		"macro-test [opts...] [--] [extras...]",
		"Tests the simple parser macro",
		"[end of arguments]",
		15);

	if (err) {
		fprintf(stderr, "Error: %s\n", err);
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

	exit_code = 0;
exit:
	free(extras); /* DO NOT free individual strings */
	return exit_code;
xopt_help:
	exit_code = 2;
	goto exit;
}
