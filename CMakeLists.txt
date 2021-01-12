cmake_minimum_required(VERSION 3.0)

project(Parson VERSION 1.0.0 DESCRIPTION "parser for json files" LANGUAGES C)

configure_file(info.h.in "${CMAKE_CURRENT_SOURCE_DIR}/include/info.h" @ONLY)

add_subdirectory(lib)

add_executable(parson src/main.c src/lexer.c)

target_include_directories(parson PUBLIC include)