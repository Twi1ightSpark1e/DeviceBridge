project('devicebridge', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

inc = include_directories('include')
src = [
    'src/main.cpp',
    'src/application.cpp'
    ]

compiler = meson.get_compiler('cpp')
cppfs_dep = compiler.find_library('c++fs')

qt5 = import('qt5')
qt5_dep = dependency('qt5', modules : [ 'Bluetooth' ])

yamlcpp_dep = dependency('yaml-cpp')

exe = executable('devicebridge', src,
    include_directories : inc, dependencies : [
        cppfs_dep,
        qt5_dep,
        yamlcpp_dep
        ])

test('basic', exe)
