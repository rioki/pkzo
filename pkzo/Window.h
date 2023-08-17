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

    //! Flag to make the window fullscreen/
    constexpr auto fullscreen = Fullscreen{};

    class PKZO_EXPORT Window
    {
    public:
        //! Create a window.
        //!
        //! These constructors will open a window. If you pass in an event router
        //! the window will emit resize events. If you pass pkzo::fullscreen instead
        //! of a size the window will be created as fullscreen in the desktop's
        //! resolution.
        //!
        //! @note The ability to phyiscally change the monitor's resolution was disabled.
        //! If you need to draw into lower resolutions due to performance reasons,
        //! you need to render to a buffer and then strech this over the window.
        //!
        //! @note IF the window is not fullscreen, it is resiabable; deal with it.
        //!
        //! @{
        Window(const glm::uvec2& size, const std::string_view caption = "Pkzo");
        Window(Fullscreen fullscreen, const std::string_view caption = "Pkzo");
        Window(EventRouter& router, const glm::uvec2& size, const std::string_view caption = "Pkzo");
        Window(EventRouter& router, Fullscreen fullscreen, const std::string_view caption = "Pkzo");
        //! @}

        ~Window();

        //! Get the window size in desktop coordinates.
        glm::uvec2 get_size() const noexcept;
        //! Get the size of drawable space.
        //!
        //! @note The difference between get_size and get_drawable_size becomes relevant
        //! on hight resolution screens as the desktop may be scaled. The get_drawable_size
        //! will comunicate the actual ammount of physical pixels to render to. Use this
        //! for rendering purposes instead of get_size.
        glm::uvec2 get_drawable_size() const noexcept;
        //! Check if the window is fullscreen.
        bool is_fullscreen() const noexcept;

        //! Make a window fullscreen.
        void make_fullscreen();
        //! Make a window windowed.
        //!
        //! @param size the initial size to set the window.
        void make_windowed(const glm::uvec2& size);

        //! Get the window caption.
        std::string get_caption() const noexcept;
        //! Set the window caption.
        void set_caption(const std::string_view value);

        //! The signal emitted when the window shall be redrawn.
        rsig::signal<>& get_draw_signal() noexcept;
        //! The signal emitted when the window was resized.
        rsig::signal<glm::uvec2>& get_resize_signal() noexcept;

        //! Redraw the windwo.
        void draw();

        //! Save the current front buffer.
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
