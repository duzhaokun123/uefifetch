cmake_minimum_required(VERSION 4.0.1)

if (NOT CMAKE_SYSTEM_PROCESSOR)
    message(FATAL_ERROR "CMAKE_SYSTEM_PROCESSOR is not set, please set it to x86_64, aarch64 or riscv64")
endif ()

set(CMAKE_SYSTEM_NAME "UEFI")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/uefi-libc/cmake")

project(uefifetch
        VERSION 0.1.0
        LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

#set(CMAKE_LINKER_TYPE "LLD")

set(COMMON_FLAGS " -fno-stack-check -mno-red-zone -fno-rtti")
string(APPEND CMAKE_C_FLAGS " ${COMMON_FLAGS}")
string(APPEND CMAKE_CXX_FLAGS " ${COMMON_FLAGS} -fno-exceptions")

#set(COMMON_LINK_FLAGS "-Xlinker -subsystem:efi_application -Xlinker -nodefaultlib -Xlinker -entry:uefi_init")
#string(APPEND CMAKE_EXE_LINKER_FLAGS " ${COMMON_LINK_FLAGS}")

#include_directories(SYSTEM
#        posix-uefi/uefi
#        gnu-efi/inc
#        gnu-efi/inc/protocol
#        gnu-efi/inc/${CMAKE_SYSTEM_PROCESSOR}
#        fake_libc
#)

set(UEFI_GNU_EFI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gnu-efi")

add_subdirectory(uefi-libc)
#include(posix-uefi.cmake
include(lodepng.cmake)
include(cargs.cmake)

add_subdirectory(src)
