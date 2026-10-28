// © Joseph Cameron - MIT License

#include <gdk/windowing/android_context.h>
#include <gdk/windowing/android_window.h>

int main() {
    auto *const pMake = &gdk::windowing::android_context::make;

    return pMake ? 0 : 1;
}
