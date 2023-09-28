cmake_minimum_required(VERSION 3.20)
project(time_bomb C)

add_library(time_bomb STATIC
    "time_bomb_config.c"
    "time_bomb_config_user.c"
    "time_bomb_config_user.h"
    "time_bomb_user.h"
    "time_bomb_user_types.h")

add_subdirectory("${PROJECT_SOURCE_DIR}/../../hsm" hsm)

target_include_directories(time_bomb PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(time_bomb PUBLIC hsm)