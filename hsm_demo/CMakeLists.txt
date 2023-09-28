# CMakeList.txt : CMake project for hsm_demo, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("hsm_demo")

# Add source to this project's executable.
add_executable (hsm_demo "hsm_demo.c" )

add_subdirectory("${PROJECT_SOURCE_DIR}/time_bomb" time_bomb)
target_link_libraries(hsm_demo PUBLIC time_bomb)

# TODO: Add tests and install targets if needed.
