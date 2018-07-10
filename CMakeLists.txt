cmake_minimum_required (VERSION 2.4)
project (xopt)

add_library (xopt STATIC "${CMAKE_CURRENT_SOURCE_DIR}/xopt.c")

if (APPLE OR UNIX)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic -std=c11 -D_XOPEN_SOURCE=600 -fdiagnostics-color=always -fvisibility=hidden")
	set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3 -O0")
	set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast")
endif ()

function (_xopt_test name)
	add_executable ("xopt-test-${name}" "${CMAKE_CURRENT_SOURCE_DIR}/test/${name}.c")
	target_link_libraries ("xopt-test-${name}" xopt)
	add_test (
		NAME "xopt-${name}-test"
		COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/test/test-case.sh" $<TARGET_FILE:xopt-test-${name}> "${CMAKE_CURRENT_SOURCE_DIR}/test/${name}.out" ${ARGN}
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/test")
endfunction ()

if (BUILD_TESTING)
	enable_testing ()
	_xopt_test (simple --some-int=10 --some-double=14.5 foo bar -- --some-other=20)
	_xopt_test (macro --some-int=10 --some-double=14.5 foo bar -- --some-other=20)
	_xopt_test (required --some-int=10 --some-double=14.5 --some-required=1337 foo bar -- --some-other=20)
	_xopt_test (optional-longarg -i 10 -d 14.5 foo bar -- --some-other=20)
	_xopt_test (autohelp --help -- --is-not-passed ignoreme)
	_xopt_test (sloppyshorts -i10 -d 14.5 "-ssome string" -m -mm -mmm foo bar -- --is-not-passed ignoreme)
endif ()
