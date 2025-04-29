set(VERSION "0.1.0")

add_executable(uefifetch
        main.cpp
        stl.cpp
        utils.cpp
        modules/Shell.cpp
        modules/Locale.cpp
        modules/UEFI.cpp
        modules/Memory.cpp
        modules/PlaceHolder.cpp
        print.cpp
        modules/IP4.cpp
        modules/FS2.cpp
        modules/SMBIOS.cpp
        modules/UefiFetch.cpp
        screenshot.cpp
        modules/GOP.cpp
        modules/STOP.cpp
)

target_link_libraries(uefifetch
        posix-uefi
        lodepng
        cargs
)

target_compile_definitions(uefifetch PRIVATE
        UEFIFETCH_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
        UEFIFETCH_VERSION="${VERSION}"
)