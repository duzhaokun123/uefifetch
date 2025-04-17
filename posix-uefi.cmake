if (ARCH STREQUAL "x86_64")
    set(CRT_C ./posix-uefi/uefi/crt_x86_64.c)
elseif (ARCH STREQUAL "aarch64")
    set(CRT_C ./posix-uefi/uefi/crt_aarch64.c)
elseif (ARCH STREQUAL "riscv64")
    set(CRT_C ./posix-uefi/uefi/crt_riscv64.c)
else ()
    message(FATAL_ERROR "only x86_64, aarch64 and riscv64 are supported, this ${CMAKE_SYSTEM_PROCESSOR} is not supported")
endif ()

add_library(posix-uefi STATIC
        ${CRT_C}
        ./posix-uefi/uefi/dirent.c
        ./posix-uefi/uefi/qsort.c
        ./posix-uefi/uefi/stat.c
        ./posix-uefi/uefi/stdio.c
        ./posix-uefi/uefi/stdlib.c
        ./posix-uefi/uefi/string.c
        ./posix-uefi/uefi/time.c
        ./posix-uefi/uefi/unistd.c
)
