set(VERSION "0.1.0")

add_executable(uefifetch.efi
        main.cpp
        stl.cpp
        utils.cpp
        modules/Display.cpp
        modules/Shell.cpp
        modules/Locale.cpp
        modules/UEFI.cpp
        modules/Memory.cpp
        modules/Placeholder.cpp
        print.cpp
        modules/IP4.cpp
        modules/FS.cpp
        modules/FS2.cpp
        modules/SMBIOS.cpp
        modules/UefiFetch.cpp
        screenshot.cpp
)

target_link_libraries(uefifetch.efi
        posix-uefi
        lodepng
        cargs
)

target_compile_definitions(uefifetch.efi PRIVATE
        UEFIFETCH_ARCH="${ARCH}"
        UEFIFETCH_VERSION="${VERSION}"
)