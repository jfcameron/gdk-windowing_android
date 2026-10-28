# © Joseph Cameron - MIT License

jfc_add_tests(
    C++_STANDARD 20

    TEST_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/android_window_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/android_conformance.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/surface.cpp"

    LIBRARIES
        gdkwindowing_android
        gdkwindowing_conformance
        mediandk)

set_property(TARGET ${JFC_TEST_TARGET} PROPERTY CXX_EXTENSIONS OFF)

if (GDKWINDOWING_ANDROID_INSTALL)
    add_test(NAME gdk-windowing_android_install_and_consume
        COMMAND "${CMAKE_COMMAND}"
            "-DBUILD_DIR=${PROJECT_BINARY_DIR}"
            "-DWORK_DIR=${CMAKE_CURRENT_BINARY_DIR}/install_and_consume"
            "-DCONFIG=$<CONFIG>"
            "-DGENERATOR=${CMAKE_GENERATOR}"
            "-DNDK=${ANDROID_NDK}"
            "-DABI=${ANDROID_ABI}"
            "-DPLATFORM=${ANDROID_PLATFORM}"
            "-DCXX_FLAGS=${CMAKE_CXX_FLAGS}"
            -P "${CMAKE_CURRENT_LIST_DIR}/install/install_and_consume.cmake")
endif()
