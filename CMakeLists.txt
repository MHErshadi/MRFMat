cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

project(MRFMat VERSION 1.2.0
    DESCRIPTION "MetaReal Fast Matrix library version 0.1.0"
    LANGUAGES C ASM)
option(BUILD_SHARED_LIBS "Shared Library")

if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wpedantic")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_RELEASE "-O3")
    set(CMAKE_C_FLAGS_MINSIZEREL "-Os")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

    enable_language(ASM-ATT)
elseif (MSVC)
    set(CMAKE_C_FLAGS "/Wall /wd4324 /wd4710 /wd4711 /wd4820 /wd4996 /wd5045 /wd5105 /WX")
    set(CMAKE_C_FLAGS_DEBUG "/Od /Zi")
    set(CMAKE_C_FLAGS_RELEASE "/O2")
    set(CMAKE_C_FLAGS_MINSIZEREL "/Os")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/O2 /Zi")

    enable_language(ASM_MASM)
endif()

if (BUILD_SHARED_LIBS)
    add_compile_definitions(__MRFMAT_SHARED__)
    add_compile_definitions(__MRFMAT_COMPILE_TIME__)
endif()

add_library(MRFMat
    srcs/init.c)
target_include_directories(MRFMat PUBLIC heads PUBLIC .)

#if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
#    target_sources(MRFMat)
#elseif (MSVC)
#    target_sources(MRFMat)
#endif()

enable_testing()
#add_subdirectory(tests)
#add_subdirectory(benchmarks)

set_target_properties(MRFMat PROPERTIES PUBLIC_HEADER mrfmat.h)
install(TARGETS MRFMat
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include)
