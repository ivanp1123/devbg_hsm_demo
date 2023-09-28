cmake_minimum_required(VERSION 3.20)
project(hsm C)

add_library(hsm STATIC
    "src/hsm.c"
    "src/hsm.h"
    "src/hsm_user.h"
)

target_include_directories(hsm PUBLIC src)