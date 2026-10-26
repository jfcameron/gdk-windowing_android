// © Joseph Cameron - MIT License

#ifndef GDK_WINDOWING_ANDROID_TEST_SURFACE_H
#define GDK_WINDOWING_ANDROID_TEST_SURFACE_H

struct ANativeWindow;

namespace gdk::windowing::test {
    [[nodiscard]] ANativeWindow *a_surface();
}

#endif
