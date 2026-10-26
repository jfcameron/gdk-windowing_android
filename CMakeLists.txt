# © Joseph Cameron - MIT License

cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

if (TARGET gdkwindowing_android)
    return()
endif()

project(gdk-windowing_android
    VERSION 1.0
    DESCRIPTION "the gdk window interface, implemented over an Android activity's window and EGL"
    LANGUAGES CXX)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/jfc-cmake/jfclib.cmake")

option(GDKWINDOWING_ANDROID_BUILD_TESTS "Build unit tests" ${PROJECT_IS_TOP_LEVEL})
option(GDKWINDOWING_ANDROID_BUILD_DOCS "Build documentation" OFF)

if (GDKWINDOWING_ANDROID_BUILD_DOCS AND NOT ANDROID)
    add_subdirectory(docs)

    return()
endif()

if (NOT ANDROID)
    message(FATAL_ERROR "gdk-windowing_android builds for Android only: configure with an android-* preset")
endif()

add_subdirectory(extern)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Werror=c++20-extensions> $<$<COMPILE_LANGUAGE:CXX>:-Werror=c++23-extensions>)

add_library(gdkwindowing_android STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/android_context.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/android_window.cpp")

add_library(gdk::windowing_android ALIAS gdkwindowing_android)

set_target_properties(gdkwindowing_android PROPERTIES EXPORT_NAME windowing_android PREFIX "lib")

target_include_directories(gdkwindowing_android PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")

target_compile_features(gdkwindowing_android PUBLIC cxx_std_20)

target_link_libraries(gdkwindowing_android PUBLIC gdkwindowing EGL android)

if (GDKWINDOWING_ANDROID_BUILD_TESTS)
    add_subdirectory(test)
endif()

if (GDKWINDOWING_ANDROID_BUILD_DOCS)
    add_subdirectory(docs)
endif()
