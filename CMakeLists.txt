# Project configuration
cmake_minimum_required(VERSION 3.10)
project(TinyTCP LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find sources
if(WIN32)
message(STATUS "Making a WINDOWS build")
set(SRC
  src/windows/common.c
  src/windows/client.c
  src/windows/server.c
)
elseif(UNIX)
message(STATUS "Making a POSIX build")
set(SRC
  src/posix/common.c
  src/posix/client.c
  src/posix/server.c
)
else()
message(FATAL_ERROR "UNSUPPORTED PLATFORM ERROR: TinyTCP only supports Windows, macOS, Linux and BSD")
endif()

# Add targets
add_library(tinytcp SHARED ${SRC})

# Link dependencies (if needed)
if(WIN32)
target_link_libraries(tinytcp PRIVATE ws2_32)
endif()

# Set compile options and definitions
target_compile_definitions(tinytcp PRIVATE TINYTCP_CONFIG_BUILDING _CRT_SECURE_NO_WARNINGS)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
message(STATUS "Found compiler to be GNU or Clang.")
target_compile_options(tinytcp PRIVATE -Wall -Wextra -Wpedantic -Werror)
elseif(MSVC)
message(STATUS "Found compiler to be MSVC")
target_compile_options(tinytcp PRIVATE /W4 /WX)
endif()

# Set include directories
target_include_directories(tinytcp PUBLIC include)
