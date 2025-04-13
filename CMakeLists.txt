cmake_minimum_required(VERSION 3.30)

project(uefifetch LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CPP_STANDARD 23)

include(posix-uefi.cmake)
add_subdirectory(src)