// © Joseph Cameron - MIT License

#ifndef GDK_WINDOWING_ANDROID_CONTEXT_H
#define GDK_WINDOWING_ANDROID_CONTEXT_H

#include <gdk/windowing/context.h>

#include <memory>
#include <string_view>

struct ANativeWindow;

namespace gdk::windowing {
    class android_window;

    /// \brief the Android implementation of `gdk::windowing::context`. It makes one window at a time, on the activity's window
    class android_context final : public context {
    public:
        [[nodiscard]] static std::shared_ptr<android_context> make(ANativeWindow *const apWindow);

        //! the size is the native window's, not the one asked for.
        /// Throws gdk::windowing::exception while a window this made is still alive.
        [[nodiscard]] virtual window_ptr_type make_window(
            const std::string_view aName = "Window",
            const window_size_type aWindowSize = {400, 300},
            const vsync_mode aVsync = vsync_mode::adaptive) override;

        //! nothing to do: the activity's looper delivers Android's events
        virtual void poll_events() override;

        //! the activity's window after Android destroyed and remade it; passed on to the live window
        void set_native_window(ANativeWindow *const apWindow);

        virtual ~android_context() override = default;

    private:
        explicit android_context(ANativeWindow *const apWindow);

        ANativeWindow *m_pNativeWindow;
        std::weak_ptr<android_window> m_pWindow;
    };
}

#endif
