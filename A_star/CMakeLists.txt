cmake_minimum_required(VERSION 3.5)
project(A_star VERSION 0.1)

add_compile_options(-Wall -Wextra -Wpedantic -ggdb -std=c++20)

add_executable(A_star
				src/main.cpp
				src/Point.cpp
				src/consts.cpp
				src/AStar.cpp
				src/Grid.cpp
				src/Print.cpp)

install(TARGETS A_star DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
