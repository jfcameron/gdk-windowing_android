// © Joseph Cameron - MIT License

#ifndef GDK_WINDOWING_ANDROID_WINDOW_H
#define GDK_WINDOWING_ANDROID_WINDOW_H

#include <gdk/windowing/window.h>

#include <memory>
#include <string_view>

struct ANativeWindow;

namespace gdk::windowing {
    /// \brief an Android activity's window, drawn into with OpenGL ES 2 through EGL
    class android_window final : public window {
    public:
        //! the GL context is current on the calling thread once this returns.
        /// Throws gdk::windowing::exception without a native window, or when EGL cannot give it a GLES 2 context.
        [[nodiscard]] static std::shared_ptr<android_window> make(ANativeWindow *const apWindow,
            const std::string_view aName = "Window", const vsync_mode aVsync = vsync_mode::adaptive);

        //! the activity's window after Android destroyed and remade it; nullptr detaches until then
        void set_native_window(ANativeWindow *const apWindow);

        [[nodiscard]] bool has_native_window() const;

        virtual void set_icons(const icon_image_collection_type &aIconImages) override;
        virtual void set_cursor(const cursor_image_type &aRGBA32) override;
        virtual void set_cursor(const standard_cursor_graphic aCursor) override;
        virtual void close() override;
        virtual void keep_open() override;
        virtual void swap_buffers() override;

        [[nodiscard]] virtual std::string_view name() const override;
        [[nodiscard]] virtual window_size_type window_size() const override;
        [[nodiscard]] virtual window_aspect_ratio_type aspect_ratio() const override;
        [[nodiscard]] virtual bool should_close() const override;

        virtual ~android_window() override;

        android_window(const android_window &) = delete;
        android_window &operator=(const android_window &) = delete;

    private:
        android_window(ANativeWindow *const apWindow, const std::string_view aName, const vsync_mode aVsync);

        struct impl;
        std::unique_ptr<impl> m_pImpl;
    };
}

#endif
