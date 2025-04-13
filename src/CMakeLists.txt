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
)
target_link_libraries(uefifetch.efi posix-uefi)