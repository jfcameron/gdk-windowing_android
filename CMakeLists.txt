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
option(GDKWINDOWING_ANDROID_INSTALL "Generate install rules" ${PROJECT_IS_TOP_LEVEL})

if (GDKWINDOWING_ANDROID_BUILD_DOCS)
    jfc_generate_documentation_doxygen(
        PROJECT_LOGO     ${CMAKE_CURRENT_LIST_DIR}/docs/icon.png

        README_PATH      README.md
        OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/docs

        INCLUDE_DIRECTORIES
            include/
    )

    if (NOT ANDROID)
        return()
    endif()
endif()

if (NOT ANDROID)
    message(FATAL_ERROR "gdk-windowing_android builds for Android only: configure with an android-* preset")
endif()

add_subdirectory(extern)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Werror=c++20-extensions> $<$<COMPILE_LANGUAGE:CXX>:-Werror=c++23-extensions>)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(gdkwindowing_android STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/android_context.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/android_window.cpp")

add_library(gdk::windowing_android ALIAS gdkwindowing_android)

set_target_properties(gdkwindowing_android PROPERTIES EXPORT_NAME windowing_android PREFIX "lib")

target_include_directories(gdkwindowing_android PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_compile_features(gdkwindowing_android PUBLIC cxx_std_20)

target_link_libraries(gdkwindowing_android PUBLIC gdkwindowing EGL android)

if (GDKWINDOWING_ANDROID_INSTALL)
    install(TARGETS gdkwindowing_android
        EXPORT gdk-windowing_android-targets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")

    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    install(EXPORT gdk-windowing_android-targets
        FILE gdk-windowing_android-targets.cmake
        NAMESPACE gdk::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/gdk-windowing_android")

    write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/gdk-windowing_android-config-version.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

    file(WRITE "${PROJECT_BINARY_DIR}/gdk-windowing_android-config.cmake"
"include(CMakeFindDependencyMacro)
find_dependency(gdk-windowing 1)
include(\"\${CMAKE_CURRENT_LIST_DIR}/gdk-windowing_android-targets.cmake\")
")

    install(FILES
        "${PROJECT_BINARY_DIR}/gdk-windowing_android-config.cmake"
        "${PROJECT_BINARY_DIR}/gdk-windowing_android-config-version.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/gdk-windowing_android")
endif()

if (GDKWINDOWING_ANDROID_BUILD_TESTS)
    add_subdirectory(test)
endif()
