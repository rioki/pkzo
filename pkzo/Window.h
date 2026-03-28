// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <functional>

#include <glm/glm.hpp>
#include <rsig/rsig.h>
#include <SDL3/SDL.h>

#include "api.h"
#include "SdlSentry.h"
#include "GraphicContext.h"

namespace pkzo
{
    class MemoryTexture;

    //! Window display state.
    enum class WindowState : Uint64
    {
        WINDOW     = 0ULL,                    //!< Normal windowed mode.
        FULLSCREEN = SDL_WINDOW_FULLSCREEN,   //!< Exclusive fullscreen mode.
        MINIMIZED  = SDL_WINDOW_MINIMIZED,    //!< Minimized to taskbar.
        MAXIMIZED  = SDL_WINDOW_MAXIMIZED     //!< Maximized to fill the desktop.
    };

    //! Application window.
    //!
    //! Window manages an OS window with an associated graphics context.
    class PKZO_EXPORT Window
    {
    public:
        //! Window initialization parameters.
        struct Init
        {
            std::string title = "Pkzo";                 //!< Window title bar text.
            glm::uvec2  size  = glm::uvec2(800u, 600u); //!< Initial window size in pixels.
            WindowState state = WindowState::WINDOW;    //!< Initial display state.
            Api         api   = Api::OPENGL;            //!< Graphics API to use.
        };

        //! Construct and open a window.
        //!
        //! @param init  Initialization parameters.
        Window(Init init);

        //! Close the window and release all associated resources.
        ~Window();

        //! Get the window title.
        //!
        //! @returns The window title bar text.
        [[nodiscard]]
        std::string get_title() const;

        //! Get the current window size in pixels.
        //!
        //! @returns The window size as (width, height).
        [[nodiscard]]
        glm::uvec2 get_size() const;

        //! Set the window size in pixels.
        //!
        //! @param value  The desired size as (width, height).
        void set_size(const glm::uvec2& value);

        //! Get the drawable resolution of the window.
        //!
        //! This may differ from get_size() on high-DPI displays where
        //! the framebuffer is larger than the logical window size.
        //!
        //! @returns The framebuffer resolution as (width, height).
        [[nodiscard]]
        glm::uvec2 get_resolution() const;

        //! Get the current display state of the window.
        //!
        //! @returns The current WindowState.
        [[nodiscard]]
        WindowState get_state() const;

        //! Get the API this window uses.
        Api get_api() const;

        //! Check whether the window is in fullscreen mode.
        //!
        //! @returns True if the window is fullscreen, false otherwise.
        [[nodiscard]]
        bool get_fullscreen() const;

        //! Set fullscreen mode.
        //!
        //! @param value  True to enter fullscreen, false to return to windowed mode.
        void set_fullscreen(bool value);

        //! Capture the mouse, confining it to this window.
        //!
        //! While captured, the cursor is hidden and mouse motion is delivered
        //! as relative events. Call release_mouse() to restore normal behavior.
        void capture_mouse();

        //! Release a previously captured mouse.
        void release_mouse();

        //! Register a callback to be invoked each frame when the window is drawn.
        //!
        //! @param handler  Callback receiving the window's GraphicContext.
        //! @returns A connection object representing the registered handler.
        rsig::connection on_draw(const std::function<void (GraphicContext&)>& handler);

        //! Take a screenshot of the window.
        std::shared_ptr<MemoryTexture> screenshot() const;

        //! Render a frame, invoking all registered draw callbacks.
        void draw();

    private:
        SdlSentry                       sdl_sentry = SdlSentry{SdlSubsystem::VIDEO | SdlSubsystem::EVENTS};
        SDL_Window*                     window     = nullptr;
        std::unique_ptr<GraphicContext> graphic_context;

        rsig::signal<GraphicContext&> draw_signal;

        Window(const Window&) = delete;
        Window& operator = (const Window&) = delete;
    };
}
