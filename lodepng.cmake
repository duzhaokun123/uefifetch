add_library(lodepng STATIC
        lodepng/lodepng.cpp
)
target_compile_definitions(lodepng PUBLIC
        LODEPNG_NO_COMPILE_DECODER
        LODEPNG_NO_COMPILE_ANCILLARY_CHUNKS
        LODEPNG_NO_COMPILE_CPP
)
target_include_directories(lodepng PUBLIC
        lodepng
)