# © Joseph Cameron - MIT License

function(_run aWhat)
    execute_process(COMMAND ${ARGN} RESULT_VARIABLE _result OUTPUT_VARIABLE _output ERROR_VARIABLE _output)

    if (_result)
        message(FATAL_ERROR "${aWhat} failed (${_result}):\n${_output}")
    endif()
endfunction()

file(REMOVE_RECURSE "${WORK_DIR}")

_run("install" "${CMAKE_COMMAND}" --install "${BUILD_DIR}" --prefix "${WORK_DIR}/prefix")

_run("configuring the consumer" "${CMAKE_COMMAND}"
    -S "${CMAKE_CURRENT_LIST_DIR}"
    -B "${WORK_DIR}/build"
    -G "${GENERATOR}"
    "-DCMAKE_TOOLCHAIN_FILE=${NDK}/build/cmake/android.toolchain.cmake"
    "-DANDROID_ABI=${ABI}"
    "-DANDROID_PLATFORM=${PLATFORM}"
    "-DCMAKE_CXX_FLAGS=${CXX_FLAGS}"
    "-DCMAKE_BUILD_TYPE=${CONFIG}"
    "-DCMAKE_FIND_ROOT_PATH=${WORK_DIR}/prefix"
    "-DCMAKE_PREFIX_PATH=${WORK_DIR}/prefix")

_run("building the consumer" "${CMAKE_COMMAND}" --build "${WORK_DIR}/build")
