# XOpt [![CircleCI](https://circleci.com/gh/Qix-/xopt.svg?style=svg)](https://circleci.com/gh/Qix-/xopt)
The sane answer to POpt.

XOpt is a command line argument parsing library written in ANSI C. XOpt
accepts arguments in GNU format and focuses on clean definition, taking stress
off the implementation.

## Usage

To include in your [Meson](https://mesonbuild.com/Tutorial.html) project, unzip _or_ add as a submodule under
`subprojects/xopt` and add the following to your `meson.build`:

```meson
xopt = subproject('xopt').get_variable('dep')
executable('my-app', 'app.cc', dependencies: [xopt])
```

To include in your CMake project (deprecated):

```cmake
add_subdirectory(path/to/xopt)
include_directories(path/to/xopt)

add_executable(my-app app.c)
target_link_libraries(my-app xopt)
```

## Example

Several examples can be found in the `test/` directory. Here's a simple one:

```c
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include <xopt.h>

typedef struct {
	int someInt;
	float someFloat;
	double someDouble;
	bool help;
} SimpleConfig;

xoptOption options[] = {
	{
		"some-int", 'i',
		offsetof(SimpleConfig, someInt),
		0, XOPT_TYPE_INT,
		"n", "Some integer value. Can set to whatever number you like."
	},
	{
		"some-float", 'f',
		offsetof(SimpleConfig, someFloat),
		0, XOPT_TYPE_FLOAT,
		"n", "Some float value."
	},
	{
		"some-double", 'd',
		offsetof(SimpleConfig, someDouble),
		0, XOPT_TYPE_DOUBLE,
		"n", "Some double value."
	},
	{
		"help", '?',
		offsetof(SimpleConfig, help),
		0, XOPT_TYPE_BOOL,
		0, "Shows this help message"
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
		opts.usage = "[options] [extras...]";
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
```

# License
Originally by Josh Junon, released under [CC0](https://creativecommons.org/publicdomain/zero/1.0/). Go nuts.
