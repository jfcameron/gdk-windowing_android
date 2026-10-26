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
