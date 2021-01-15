cmake_minimum_required(VERSION 3.0)

project(ParsonLib VERSION 1.0.1 LANGUAGES C)

set(C_STANDARD 99)

add_library(parson lexer.c list.c parser.c parson.c allocator.c)

target_include_directories(parson INTERFACE ../include)

install(TARGETS parson DESTINATION lib)

install(FILES ../include/lexer.h
                ../include/list.h
                ../include/parson.h
                ../include/parser.h
                ../include/allocator.h
 DESTINATION include/parson)