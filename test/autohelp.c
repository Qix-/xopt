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
		0,
		'f',
		offsetof(SimpleConfig, someFloat),
		0,
		XOPT_TYPE_FLOAT,
		"n",
		"Some float value."
	},
	{
		"some-double",
		0,
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

	XOPT_SIMPLE_PARSE(
		"autohelp-test-case",
		0,
		&options[0], &config,
		argc, argv,
		&extraCount, &extras,
		&err,
		stderr,
		"[opts...] [--] [extras...]",
		"Tests the simple parser macro",
		"[end of arguments]",
		15);

	if (!err) {
		err = config.help
			? "--help was passed but autohelp didn't fire"
			: "--help was not passed - it is required for this test case";
	}

	fprintf(stderr, "Error: %s\n", err);

exit:
	free(extras); /* DO NOT free individual strings */
	return exit_code;
xopt_help:
	exit_code = 0;
	goto exit;
}
