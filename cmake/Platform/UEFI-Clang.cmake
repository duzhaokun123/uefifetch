macro(__uefi_compiler_clang lang)
    set(CMAKE_${lang}_USING_LINKER_LLD "-fuse-ld=lld")
endmacro()