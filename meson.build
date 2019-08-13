project('devicebridge', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

inc = include_directories('include')
src = [
    'src/main.cpp'
    ]

compiler = meson.get_compiler('cpp')
cppfs_dep = compiler.find_library('c++fs')

cmake = import('cmake')

libblepp_proj = cmake.subproject('libblepp')
libblepp_dep  = libblepp_proj.dependency('ble++')

exe = executable('devicebridge', src,
    include_directories : inc, dependencies : [
        cppfs_dep,
        libblepp_dep
        ])

test('basic', exe)
