aux_source_directory(. SRC)
aux_source_directory(modules MODULES)
aux_source_directory(protocols PROTOCOLS)

add_executable(uefifetch
        ${SRC}
        ${MODULES}
        ${PROTOCOLS}
)

target_link_libraries(uefifetch
        uefi-libc
        lodepng
        cargs
)

configure_file(
        version.h.in
        generated/version.h
        @ONLY
)

target_include_directories(uefifetch PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/generated
)