# CMakeList.txt : CMake project for test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("test")

# Add source to this project's executable.
add_executable (test "test.c"  "test_sm_config.c" ${PROJECT_SOURCE_DIR}/../hsm/src/hsm.c "test_sm_config_user.c" "test_env.c")

# Link to unity test framework
add_subdirectory(${PROJECT_SOURCE_DIR}/unity ${PROJECT_SOURCE_DIR}/unity/lib)

target_compile_definitions(test PUBLIC -D UTEST)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/../hsm/src PUBLIC ${PROJECT_SOURCE_DIR}/../cfg)
target_link_libraries(test PUBLIC unity)


# TODO: Add tests and install targets if needed.
