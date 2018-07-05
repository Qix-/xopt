cmake_minimum_required (VERSION 2.4)
project (xopt)

add_library (xopt STATIC "${CMAKE_CURRENT_SOURCE_DIR}/xopt.c")

function (_xopt_test name)
	add_executable ("xopt-test-${name}" "${CMAKE_CURRENT_SOURCE_DIR}/test/${name}.c")
	target_link_libraries ("xopt-test-${name}" xopt)
	add_test (
		NAME "xopt-${name}-test"
		COMMAND $<TARGET_FILE:xopt-test-${name}> ${ARGN}
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/test")
endfunction ()

if (BUILD_TESTING)
	enable_testing ()
	_xopt_test (simple "--some-int=10" "--some-double=14.5")
	_xopt_test (macro --some-int=10 --some-double=14.5)
	_xopt_test (required --some-int=10 --some-double=14.5 --some-required=1337)
endif ()
