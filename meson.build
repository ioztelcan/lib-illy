project('name', 'cpp',
  version : '0.1',
  default_options : [
	  				'warning_level=3', # Wall
  					'buildtype=debugoptimized', #-O2, debug=true
					'cpp_std=c++17',
					'werror=true', # Werror
					'b_sanitize=address', # Address sanitizer
					'b_sanitize=undefined', # UB sanitizer
					'b_lundef=false', # Required to make ubsan work with clang according to meson
					])

compiler_flags = []
linker_flags = []
add_global_arguments(compiler_flags, language: 'cpp')

# Add module subdirectories here.
# subdir()

# Add module include locations and shared libraries to link with here.
include_dirs = ['src']
include = include_directories(include_dirs)
link_libs = []

bin = executable('main',
			     'main.cpp',
			     include_directories: include,
			     link_with: link_libs,
			     link_args: linker_flags)

# Flags to use gtest and/or catch2 as a unit test system
use_gtest = false
use_catch2 = false

if use_gtest == true
message('=== GTEST ENABLED ===')
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')

gtest_src = [
	'test/gtest_main.cpp',
  	'test/gtest_sample_test.cpp',
]

gtest_bin = executable('gtest-test',
					  gtest_src,
					  include_directories: include,
  					  dependencies : [
    					gtest_dep,
    					gmock_dep],
  					  link_with : link_libs,
					  link_args: linker_flags)

test('gtest-test', gtest_bin)
endif

if use_catch2 == true
message('=== CATCH2 ENABLED ===')
catch2_proj = subproject('catch2')
catch2_dep = catch2_proj.get_variable('catch2_dep')

catch2_test_src = ['test/catch2_sample_test.cpp']

catch2_bin = executable('catch2-test',
					  catch2_test_src,
					  include_directories: include,
  					  dependencies : [
						catch2_dep],
  					  link_with : link_libs,
					  link_args: linker_flags)

test('catch2-test', catch2_bin)
endif




