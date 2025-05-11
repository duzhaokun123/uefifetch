add_library(cargs STATIC
        cargs/src/cargs.c
)

target_include_directories(cargs PUBLIC
        cargs/include
)
target_link_libraries(cargs PUBLIC
    uefi-libc
)