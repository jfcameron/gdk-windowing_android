# gdk-windowing_android
The [gdk-windowing](https://github.com/jfcameron/gdk-windowing) interface, implemented over an Android activity's window: an OpenGL ES 2 context through EGL.

API documentation: https://jfcameron.github.io/gdk-windowing_android/

## Getting Started
Install cmake 3.21 or greater and an Android NDK (r23 or later; r27c's 128-bit `long double` division is wrong, so prefer a newer one), and set `ANDROID_NDK_HOME` to it.
```
# initialize the tree
git submodule update --init --recursive

# generate the script to build the library and its tests for an x86_64 emulator
cmake --preset android-x86_64

# build the library and tests
cmake --build --preset android-x86_64

# run the tests on the device or emulator adb is connected to
ctest --preset android-x86_64
```
The tests draw into an `AImageReader`'s surface, so they need no activity: a plain executable run through adb is enough.

See `CMakePresets.json` for the ABIs, and `.github/workflows/ci.yml` to see how CI builds them and runs the tests on emulators at API 24, the lowest supported, and API 34.

To use it from another project, add it with `add_subdirectory` and link `gdk::windowing_android`. It brings gdk-windowing with it, unless the project already has it. Or install it (`cmake --install`, which installs gdk-windowing beside it) and use `find_package(gdk-windowing_android)`.

## Usage
The activity owns the window, so the context is made from it, and makes one window at a time on it:

```cpp
#include <gdk/windowing/android_context.h>
#include <gdk/windowing/window.h>

using namespace gdk::windowing;

// in the activity, once Android gives you its ANativeWindow
const auto pContext = android_context::make(pNativeWindow);
const window_ptr_type pWindow = pContext->make_window("my game");

// each frame: draw, into pWindow->window_size() pixels
pWindow->swap_buffers();

// when Android destroys the native window, and when it makes a new one
pContext->set_native_window(nullptr);
pContext->set_native_window(pNewNativeWindow);
```

`poll_events` does nothing: the activity's looper delivers Android's events. Icons and cursors are accepted and ignored.
