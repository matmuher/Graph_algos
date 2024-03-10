cmake_minimum_required(VERSION 3.5)
project(A_star VERSION 0.1)

add_compile_options(-Wall -Wextra -Wpedantic -ggdb -std=c++20)

add_executable(A_star
				src/glad.c

				src/main.cpp
				src/Point.cpp
				src/consts.cpp
				src/AStar.cpp
				src/Grid.cpp
				src/Print.cpp

	            src/Shader.cpp
				)

target_include_directories(A_star PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_link_libraries(A_star glfw GL X11 pthread Xrandr Xi dl)

install(TARGETS A_star DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
