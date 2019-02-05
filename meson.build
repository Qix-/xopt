project('xopt', 'c', default_options : ['c_std=c89'])

strict_args = ['-Wall', '-Werror', '-Wextra', '-pedantic', '-ansi'] # TODO support windows a bit better

# Main library
inc = include_directories('.')
lib = static_library('xopt', 'xopt.c', cpp_args: strict_args)
dep = declare_dependency(include_directories: inc, link_with: lib)

# Tests
test_specs = {
  'simple': [
    [false, ['--some-int=10', '--some-double=14.5', 'foo', 'bar', '--', '--some-other=20']]
  ],
  'macro': [
    [false, ['--some-int=10', '--some-double=14.5', 'foo', 'bar', '--', '--some-other=20']]
  ],
  'required': [
    [false, ['--some-int=10', '--some-double=14.5', '--some-required=1337', 'foo', 'bar', '--', '--some-other=20']]
  ],
  'optional-longarg': [
    [false, ['-i', '10', '-d', '14.5', 'foo', 'bar', '--', '--some-other=20']]
  ],
  'autohelp': [
    [false, ['--help', '--', '--is-not-passed', 'ignoreme']]
  ],
  'sloppyshorts': [
    [false, ['-i10', '-d', '14.5', '-ssome string', '-m', '-mm', '-mmm', 'foo', 'bar', '--', '--is-not-passed', 'ignoreme']]
  ],
  'nocondense-sloppy': [
    [true, ['-i', '10', '-d', '14.5', '-s', 'some string', '-m', '-mm', '-mmm', 'foo', 'bar', '--', '--is-not-passed', 'ignoreme']],
    [true, ['-i', '10', '-d', '14.5', '-ssome string', '-m', '-mm', '-mmm', 'foo', 'bar', '--', '--is-not-passed', 'ignoreme']],
    [false, ['-i', '10', '-d', '14.5', '-ssome string', '-m', '-m', '-m', '-m', '-m', '-m', 'foo', 'bar', '--', '--is-not-passed', 'ignoreme']]
  ],
  'nocondense': [
    [true, ['-i', '10', '-d', '14.5', '-ssome string', '-m', '-mm', '-mmm', 'foo', 'bar', '--', '--is-not-passed', 'ignoreme']]
  ]
}

foreach name, argspecs : test_specs
  exe = executable(
    name,
    join_paths('test', name + '.c'),
    dependencies: [dep],
    override_options: ['c_std=c99'],
    cpp_args: strict_args)

  i = 0
  foreach argspec : argspecs
    i = i + 1
    test(
      '@0@-@1@'.format(name, i),
      exe,
      args: argspec[1],
      should_fail: argspec[0],
      is_parallel: true,
      timeout: 1)
  endforeach
endforeach
