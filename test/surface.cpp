// © Joseph Cameron - MIT License

#include "surface.h"

#include <media/NdkImageReader.h>

#include <stdexcept>

namespace {
    void consume(void *, AImageReader *const apReader) {
        AImage *pImage = nullptr;

        if (AImageReader_acquireLatestImage(apReader, &pImage) == AMEDIA_OK && pImage) AImage_delete(pImage);
    }

    struct reader final {
        AImageReader *pReader{nullptr};
        ANativeWindow *pWindow{nullptr};
        AImageReader_ImageListener listener{nullptr, consume};

        reader() {
            if (AImageReader_new(64, 48, AIMAGE_FORMAT_RGBA_8888, 4, &pReader) != AMEDIA_OK &&
                AImageReader_new(64, 48, AIMAGE_FORMAT_YUV_420_888, 4, &pReader) != AMEDIA_OK)
                throw std::runtime_error("AImageReader_new failed");

            AImageReader_setImageListener(pReader, &listener);

            if (AImageReader_getWindow(pReader, &pWindow) != AMEDIA_OK)
                throw std::runtime_error("AImageReader_getWindow failed");
        }
    };
}

ANativeWindow *gdk::windowing::test::a_surface() {
    static const reader *const pSurface = new reader();

    return pSurface->pWindow;
}
