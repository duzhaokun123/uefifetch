set(CMAKE_SYSTEM "Linux")
set(CMAKE_SYSTEM_PROCESSOR "aarch64")
set(ARCH "aarch64")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(COMMON_FLAGS "-fshort-wchar -fno-strict-aliasing -ffreestanding -fno-stack-protector -fno-stack-check -mno-red-zone --target=aarch64-pc-win32-coff -Wno-builtin-requires-header -Wno-incompatible-library-redeclaration -Wno-long-long -DHAVE_USE_MS_ABI -fno-rtti")

set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_FLAGS ${COMMON_FLAGS})
set(CMAKE_C_LINK_EXECUTABLE "lld -flavor link -subsystem:efi_application -nodefaultlib -entry:uefi_init <OBJECTS> <LINK_LIBRARIES> -out:<TARGET>")
#set(CMAKE_C_COMPILER_WORKS 1)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -fno-exceptions")
set(CMAKE_CXX_LINK_EXECUTABLE "lld -flavor link -subsystem:efi_application -nodefaultlib -entry:uefi_init <OBJECTS> <LINK_LIBRARIES> -out:<TARGET>")

set(INCLUDE_DIRECTORIES "")
include_directories(SYSTEM ./gnu-efi/inc ./gnu-efi/inc/protocol ./gnu-efi/inc/aarch64)