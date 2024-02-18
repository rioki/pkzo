
#include "pch.h"

#include <glow/glow.h>
#include <pkzo/Window.h>

TEST(FrameBuffer, build_frame_buffer)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, testing::get_test_name(), glm::uvec2(800u, 600u), pkzo::WindowMode::WINDOWED};

    std::unique_ptr<glow::FrameBuffer> frame_buffer;

    window.init([&](){
        glow::init();

        frame_buffer = std::make_unique<glow::FrameBuffer>(glm::uvec2(800u, 600u));

        EXPECT_EQ(frame_buffer->get_size(), glm::uvec2(800u, 600u));
    });
}
