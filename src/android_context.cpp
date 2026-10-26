// © Joseph Cameron - MIT License

#include <gdk/windowing/android_context.h>

#include <gdk/windowing/android_window.h>
#include <gdk/windowing/exception.h>

using namespace gdk::windowing;

android_context::android_context(ANativeWindow *const apWindow)
: m_pNativeWindow(apWindow)
{}

std::shared_ptr<android_context> android_context::make(ANativeWindow *const apWindow) {
    return std::shared_ptr<android_context>(new android_context(apWindow));
}

window_ptr_type android_context::make_window(const std::string_view aName, const window_size_type,
    const vsync_mode aVsync) {
    if (!m_pWindow.expired())
        throw exception("gdk::windowing::android_context: the activity has one window, and a window this made "
            "still has it");

    auto pWindow = android_window::make(m_pNativeWindow, aName, aVsync);

    m_pWindow = pWindow;

    return pWindow;
}

void android_context::poll_events() {}

void android_context::set_native_window(ANativeWindow *const apWindow) {
    m_pNativeWindow = apWindow;

    if (const auto pWindow = m_pWindow.lock()) pWindow->set_native_window(apWindow);
}
