cmake_minimum_required (VERSION 3.6)
project (my_lib)
add_executable(my_lib main.cc my_template.h tools.h number_theory.h string_algorithms.h segment_tree.h)
add_definitions(-DHOME -D_CRT_SECURE_NO_WARNINGS -DNOMINMAX) 

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT my_lib) 