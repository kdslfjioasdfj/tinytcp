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
add_library(tinytcp_dyn SHARED ${SRC})
add_library(tinytcp_stat STATIC ${SRC})
add_library(tinytcp ALIAS tinytcp_dyn)

# Link dependencies (if needed)
if(WIN32)
target_link_libraries(tinytcp_dyn PRIVATE ws2_32)
target_link_libraries(tinytcp_stat PRIVATE ws2_32)
endif()

# Set compile options and definitions
target_compile_definitions(tinytcp_dyn PRIVATE TINYTCP_CONFIG_BUILDING _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(tinytcp_stat PRIVATE TINYTCP_CONFIG_BUILDING _CRT_SECURE_NO_WARNINGS)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
message(STATUS "Found compiler to be GNU or Clang.")
target_compile_options(tinytcp_dyn PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_options(tinytcp_stat PRIVATE -Wall -Wextra -Wpedantic -Werror)
elseif(MSVC)
message(STATUS "Found compiler to be MSVC")
target_compile_options(tinytcp_dyn PRIVATE /W4 /WX)
target_compile_options(tinytcp_stat PRIVATE /W4 /WX)
endif()

# Set include directories
target_include_directories(tinytcp_dyn PUBLIC include)
target_include_directories(tinytcp_stat PUBLIC include)

# Set up examples
add_executable(example_server examples/server.c)
add_executable(example_client examples/client.c)
target_include_directories(example_server PRIVATE include)
target_include_directories(example_client PRIVATE include)
target_compile_definitions(example_server PRIVATE _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(example_client PRIVATE _CRT_SECURE_NO_WARNINGS)
target_link_libraries(example_server PRIVATE tinytcp_stat)
target_link_libraries(example_client PRIVATE tinytcp_stat)
if(WIN32)
target_link_libraries(example_server PRIVATE ws2_32)
target_link_libraries(example_client PRIVATE ws2_32)
endif()