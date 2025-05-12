cmake_minimum_required(VERSION 4.0.1)

project(uefifetch
        VERSION 0.1.0
        LANGUAGES C CXX
)

if (NOT CMAKE_SYSTEM_NAME STREQUAL "UEFI")
    message(WARNING "Not building for UEFI, make sure you know what you are doing")
endif ()

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

set(COMMON_FLAGS " -fno-stack-check -mno-red-zone -fno-rtti -flto")
string(APPEND COMMON_FLAGS " -O0") # do not optimize, break lodepng
string(APPEND CMAKE_C_FLAGS " ${COMMON_FLAGS}")
string(APPEND CMAKE_CXX_FLAGS " ${COMMON_FLAGS} -fno-exceptions")

include(lodepng.cmake)
include(cargs.cmake)

add_subdirectory(src)
