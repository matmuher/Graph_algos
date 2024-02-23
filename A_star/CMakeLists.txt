cmake_minimum_required(VERSION 3.5)
project(A_star VERSION 0.1)

add_compile_options(-Wall -Wextra -Wpedantic -ggdb)

add_executable(A_star
				src/main.cpp)

install(TARGETS A_star DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
