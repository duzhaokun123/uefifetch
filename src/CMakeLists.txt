set(VERSION "0.1.0")

aux_source_directory(. SRC)
aux_source_directory(modules MODULES)
aux_source_directory(protocols PROTOCOLS)

add_executable(uefifetch
        ${SRC}
        ${MODULES}
        ${PROTOCOLS}
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