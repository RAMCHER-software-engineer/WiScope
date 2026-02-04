cmake_minimum_required(VERSION 3.16)
project(WiScope LANGUAGES CXX ASM_NASM ASM)

set(CMAKE_CXX_STANDARD 17)

# 1. Auto-detect architecture system
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    message(STATUS "Detected ARM64 architecture")
    set(ASM_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/asm/arm64/check_root.s)
    enable_language(ASM)
else()
    message(STATUS "Detected x86_64 architecture")
    set(ASM_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/asm/x86_64/check_root.asm)
    enable_language(ASM_NASM)
endif()

# 2. Search binary source files
file(GLOB_RECURSE CPPS "src/*.cpp")

# 3. Create executable target
add_executable(WiScope 
    src/main.cpp 
    src/ui/TerminalUI.cpp 
    src/core/Sniffer.cpp
    src/core/Executor.cpp 
    ${ASM_SOURCE}
)

# 4. Include directories
target_include_directories(WiScope PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)