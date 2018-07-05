#!/bin/bash

#
# To be used with CMake builds located in <xopt>/build/
#

set -uo pipefail
exec >&2

name="$1"
shift 1

function die {
	echo -e "error: $*"
	exit 1
}

cd "$(dirname "$0")"

casebin="$(pwd)/../build/xopt-test-${name}"
caseout="$(pwd)/${name}.out"

if [ -z "$name" ]; then
	die 'no test case specified'
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

diff="$(diff --suppress-common-lines -d -t "$caseout" - <<< "$output" 2>&1)"
if [ ! -z "$diff" ]; then
	die "xopt test case failed: '$name'\n$diff"
fi
