aux_source_directory(. SRC)
aux_source_directory(modules MODULES)
aux_source_directory(protocols PROTOCOLS)

add_executable(uefifetch
        ${SRC}
        ${MODULES}
        ${PROTOCOLS}
)

target_link_libraries(uefifetch
        lodepng
        cargs
)

target_include_directories(uefifetch PUBLIC
        ../gnu-efi/inc
        ../gnu-efi/inc/protocol
        ../gnu-efi/inc/${CMAKE_SYSTEM_PROCESSOR}
)

configure_file(
        version.h.in
        generated/version.h
        @ONLY
)

target_include_directories(uefifetch PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/generated
        cxx_include
)