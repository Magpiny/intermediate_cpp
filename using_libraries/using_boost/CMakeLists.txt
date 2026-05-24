cmake_minimum_required(VERSION 4.2)
project(boost_demo CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Tell CMake to put all fetched deps in your libs/ folder ──────────────────
# This overrides the default which hides them in build/
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/libs)

include(FetchContent)

# ── Fetch only the Boost libraries you actually need ─────────────────────────
# Boost is modular — each sub-library is a separate repo
# We fetch headers only — no building Boost from source

# Boost.Math — interpolation, statistics, distributions
FetchContent_Declare(
    boost_math
    GIT_REPOSITORY https://github.com/boostorg/math.git
    GIT_TAG        boost-1.87.0
    GIT_SHALLOW    TRUE          # only latest commit — faster download
    SOURCE_DIR     ${CMAKE_SOURCE_DIR}/libs/boost_math
)

# Boost.Math depends on these — must fetch them too
FetchContent_Declare(
    boost_config
    GIT_REPOSITORY https://github.com/boostorg/config.git
    GIT_TAG        boost-1.87.0
    GIT_SHALLOW    TRUE
    SOURCE_DIR     ${CMAKE_SOURCE_DIR}/libs/boost_config
)

FetchContent_Declare(
    boost_core
    GIT_REPOSITORY https://github.com/boostorg/core.git
    GIT_TAG        boost-1.87.0
    GIT_SHALLOW    TRUE
    SOURCE_DIR     ${CMAKE_SOURCE_DIR}/libs/boost_core
)

FetchContent_Declare(
    boost_assert
    GIT_REPOSITORY https://github.com/boostorg/assert.git
    GIT_TAG        boost-1.87.0
    GIT_SHALLOW    TRUE
    SOURCE_DIR     ${CMAKE_SOURCE_DIR}/libs/boost_assert
)

FetchContent_Declare(
    boost_predef
    GIT_REPOSITORY https://github.com/boostorg/predef.git
    GIT_TAG        boost-1.87.0
    GIT_SHALLOW    TRUE
    SOURCE_DIR     ${CMAKE_SOURCE_DIR}/libs/boost_predef
)

FetchContent_Declare(
    boost_static_assert
    GIT_REPOSITORY https://github.com/boostorg/static_assert.git
    GIT_TAG        boost-1.87.0
    GIT_SHALLOW    TRUE
    SOURCE_DIR     ${CMAKE_SOURCE_DIR}/libs/boost_static_assert
)

FetchContent_Declare(
    boost_throw_exception
    GIT_REPOSITORY https://github.com/boostorg/throw_exception.git
    GIT_TAG        boost-1.87.0
    GIT_SHALLOW    TRUE
    SOURCE_DIR     ${CMAKE_SOURCE_DIR}/libs/boost_throw_exception
)

# Make all declared content available
FetchContent_MakeAvailable(
    boost_config
    boost_core
    boost_assert
    boost_predef
    boost_static_assert
    boost_throw_exception
    boost_math
)

# ── Your executable ───────────────────────────────────────────────────────────
add_executable(demo src/main.cpp)

# ── Wire up the include paths ─────────────────────────────────────────────────
target_include_directories(demo PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/boost_math/include
    ${CMAKE_SOURCE_DIR}/libs/boost_config/include
    ${CMAKE_SOURCE_DIR}/libs/boost_core/include
    ${CMAKE_SOURCE_DIR}/libs/boost_assert/include
    ${CMAKE_SOURCE_DIR}/libs/boost_predef/include
    ${CMAKE_SOURCE_DIR}/libs/boost_static_assert/include
    ${CMAKE_SOURCE_DIR}/libs/boost_throw_exception/include
)

target_compile_options(demo PRIVATE
    -Wall -Wextra -Wpedantic
    -march=native
)
