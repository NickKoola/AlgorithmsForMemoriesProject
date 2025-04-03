cmake_minimum_required(VERSION 3.10)  # Updated to 3.10 or later
project(Levenshtein VERSION 0.1.0 LANGUAGES C CXX)

# Set the C++ standard to C++17 or later
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure debug symbols are included
set(CMAKE_BUILD_TYPE Debug)

# Add executable
add_executable(Levenshtein main.cpp Word.cpp Code.cpp Export.cpp)

# Enable debugging flags (for GCC/Clang)
target_compile_options(Levenshtein PRIVATE -g)

# Link the filesystem library (for GCC/Clang only)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_libraries(Levenshtein PRIVATE stdc++fs)
endif()

# Optional: If using Clang, enable LLDB debugging
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_LLVM_COMPILE_FLAGS "-ggdb")
endif()

# Optional: If using MSVC, enable debug symbols
if(MSVC)
    target_compile_options(Levenshtein PRIVATE /Zi)
endif()
