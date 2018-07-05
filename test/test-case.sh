#!/bin/bash

#
# To be used with CMake builds located in <xopt>/build/
#

set -uo pipefail
exec >&2

casebin="$1"
caseout="$2"
shift 2

function die {
	echo -e "error: $*"
	exit 1
}

cd "$(dirname "$0")"

if [ -z "$casebin" ]; then
	die 'no test case executable specified'
fi

if [ -z "$caseout" ]; then
	die 'no test case output (some-case.out) specified'
fi

if [ ! -x "$casebin" ]; then
	die "test case does not exist or is not executable: $casebin"
fi

if [ ! -f "$caseout" ]; then
	die "test case expected output file does not exist: $caseout"
fi

output="$("$casebin" "$@" 2>&1)"
r=$?
if [ $r -ne 0 ]; then
	die "$output"
fi

diff="$(diff -U0 -d -t "$caseout" - <<< "$output" 2>&1)"
if [ ! -z "$diff" ]; then
	die "xopt test case failed: '$name'\n$diff"
fi
