set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(TARGET_NAME stardust)

cmake_minimum_required(VERSION 3.25)
project(${TARGET_NAME} LANGUAGES CXX)

if (CMAKE_VERSION VERSION_LESS 3.25)
    message(FATAL_ERROR "CMake 3.25 or newer is required. Found ${CMAKE_VERSION}")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 17.0)
        message(FATAL_ERROR "Clang/AppleClang 17.0.0 or newer is required. Found ${CMAKE_CXX_COMPILER_VERSION}")
    endif()
else()
    message(WARNING "Non-Clang compiler detected: ${CMAKE_CXX_COMPILER_ID}. Clang 17+ is recommended.")
endif()

# Automatically collect all .cpp files
file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

find_package(Threads REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE Threads::Threads)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ccsds_simulator PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
