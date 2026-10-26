// © Joseph Cameron - MIT License

#include "conformance.h"
#include "surface.h"

#include <gdk/windowing/android_context.h>

namespace gdk::windowing::conformance {
    context_ptr_type make_context() { return android_context::make(test::a_surface()); }

    std::string_view implementation() { return "android"; }
}
