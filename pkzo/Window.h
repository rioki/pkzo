// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once
#include "config.h"

#include <string>
#include <string_view>

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include <glm/glm.hpp>
#include <rsig/rsig.h>

#include "SdlInit.h"

namespace pkzo
{
    class EventRouter;
    class Texture;

    struct Fullscreen {};
    constexpr auto fullscreen = Fullscreen{};

    class PKZO_EXPORT Window
    {
    public:
        Window(const glm::uvec2& size, const std::string_view caption = "Pkzo");
        Window(Fullscreen fullscreen, const std::string_view caption = "Pkzo");
        Window(EventRouter& router, const glm::uvec2& size, const std::string_view caption = "Pkzo");
        Window(EventRouter& router, Fullscreen fullscreen, const std::string_view caption = "Pkzo");

        ~Window();

        glm::uvec2 get_size() const noexcept;
        glm::uvec2 get_drawable_size() const noexcept;
        bool is_fullscreen() const noexcept;

        void make_fullscreen();
        void make_windowed(const glm::uvec2& size);

        std::string get_caption() const noexcept;
        void set_caption(const std::string_view value);

        rsig::signal<>& get_draw_signal() noexcept;
        rsig::signal<glm::uvec2>& get_resize_signal() noexcept;

        void draw();

        std::shared_ptr<Texture> save_screen() const;

    private:
        SdlInit sdl_init;

        EventRouter*     router = nullptr;
        rsig::connection router_connection;

        SDL_Window*   window;
        SDL_GLContext glcontext;

        rsig::signal<>           draw_signal;
        rsig::signal<glm::uvec2> resize_signal;

        Window(EventRouter* router, const glm::uvec2& size, unsigned int flags, const std::string_view caption);
        void handle_events(const SDL_Event& event);
    };
}
