// © Joseph Cameron - MIT License

#include <jfc/catch.hpp>

#include "surface.h"

#include <gdk/windowing/android_context.h>
#include <gdk/windowing/android_window.h>
#include <gdk/windowing/exception.h>

using namespace gdk::windowing;

TEST_CASE("an android window needs the activity's window to start with", "[android]")
{
    REQUIRE_THROWS_AS(android_window::make(nullptr), exception);
}

TEST_CASE("an android window's size is its surface's, whatever was asked", "[android]")
{
    const auto pContext = android_context::make(test::a_surface());
    const auto pWindow = pContext->make_window("sized", {1920, 1080});

    REQUIRE(pWindow->window_size() == window_size_type{64, 48});
}

TEST_CASE("an android context makes one window at a time", "[android][context]")
{
    const auto pContext = android_context::make(test::a_surface());

    auto pFirst = pContext->make_window("first");

    REQUIRE_THROWS_AS(pContext->make_window("second"), exception);

    pFirst.reset();

    REQUIRE(pContext->make_window("after")->name() == "after");
}

TEST_CASE("an android window survives losing and regaining the activity's window", "[android]")
{
    const auto pContext = android_context::make(test::a_surface());
    const auto pWindow = std::static_pointer_cast<android_window>(pContext->make_window("paused"));

    REQUIRE(pWindow->has_native_window());

    pContext->set_native_window(nullptr);

    REQUIRE_FALSE(pWindow->has_native_window());
    REQUIRE_NOTHROW(pWindow->swap_buffers());

    pContext->set_native_window(test::a_surface());

    REQUIRE(pWindow->has_native_window());
    REQUIRE_NOTHROW(pWindow->swap_buffers());
}
