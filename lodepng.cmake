add_library(lodepng STATIC
        lodepng/lodepng.cpp
)
target_compile_definitions(lodepng PUBLIC
#        LODEPNG_NO_COMPILE_ZLIB
#        LODEPNG_NO_COMPILE_PNG
        LODEPNG_NO_COMPILE_DECODER
#        LODEPNG_NO_COMPILE_ENCODER
#        LODEPNG_NO_COMPILE_DISK
        LODEPNG_NO_COMPILE_ANCILLARY_CHUNKS
#        LODEPNG_NO_COMPILE_ERROR_TEXT
#        LODEPNG_NO_COMPILE_ALLOCATORS
#        LODEPNG_NO_COMPILE_CRC
        LODEPNG_NO_COMPILE_CPP
)
target_include_directories(lodepng PUBLIC
        lodepng
)
