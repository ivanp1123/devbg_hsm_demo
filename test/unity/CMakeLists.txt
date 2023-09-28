add_library(unity STATIC
    "src/unity.c"
)

target_include_directories(unity PUBLIC src)
target_compile_definitions(unity PUBLIC ${ROOT_COMPILE_DEFS})
target_compile_options(unity PUBLIC ${ROOT_COMPILE_OPTIONS})
target_link_options(unity PUBLIC ${ROOT_LINK_OPTIONS})