//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#ifndef _PKZO_WINDOW_H_
#define _PKZO_WINDOW_H_

#include "config.h"

#include <string>
#include <string_view>
#include <functional>
#include <glm/fwd.hpp>

#include "enums.h"
#include "SdlSentry.h"

struct SDL_Window;
typedef void *SDL_GLContext;
union SDL_Event;

namespace pkzo
{
    class Texture;

    class PKZO_EXPORT Window
    {
    public:
        //! Get the number of attached displays.
        static unsigned int get_display_count() noexcept;
        //! Get the valid resolutions of the given display.
        static std::vector<glm::uvec2> get_valid_reslutions(unsigned int desktop = 0) noexcept;

        Window(const glm::uvec2& size, WindowMode mode, const std::string_view caption);
        Window(const Window&) = delete;
        ~Window();
        Window& operator = (const Window&) = delete;

        void set_caption(const std::string_view text) noexcept;
        std::string get_caption() const noexcept;

        void set_cursor_position(glm::ivec2 pos) noexcept;
        glm::ivec2 get_cursor_position() const noexcept;

        void resize(const glm::uvec2& size, WindowMode flags);
        glm::uvec2 get_size() const noexcept;
        WindowMode get_mode() const noexcept;

        void close();

        void on_draw(const std::function<void ()>& cb);
        void on_show(const std::function<void ()>& cb);
        void on_hide(const std::function<void ()>& cb);
        void on_exposed(const std::function<void ()>& cb);
        void on_moved(const std::function<void (glm::ivec2)>& cb);
        void on_resized(const std::function<void (glm::uvec2)>& cb);
        void on_size_changed(const std::function<void (glm::uvec2)>& cb);
        void on_minimixed(const std::function<void ()>& cb);
        void on_maximixed(const std::function<void ()>& cb);
        void on_restore(const std::function<void ()>& cb);
        void on_enter(const std::function<void ()>& cb);
        void on_leave(const std::function<void ()>& cb);
        void on_gain_focus(const std::function<void ()>& cb);
        void on_lose_focus(const std::function<void ()>& cb);
        void on_close(const std::function<void ()>& cb);

        void draw() const noexcept;
        //! Save the current window content.
        std::shared_ptr<Texture> save() const noexcept;

    private:
        SdlSentry                sdl_sentry;

        SDL_Window*              window    = nullptr;
        SDL_GLContext            glcontext = nullptr;

        std::function<void ()>           draw_cb;
        std::function<void ()>           show_cb;
        std::function<void ()>           hide_cb;
        std::function<void ()>           exposed_cb;
        std::function<void (glm::ivec2)> moved_cb;
        std::function<void (glm::uvec2)> size_changed_cb;
        std::function<void (glm::uvec2)> resized_cb;
        std::function<void ()>           minimize_cb;
        std::function<void ()>           maximize_cb;
        std::function<void ()>           restore_cb;
        std::function<void ()>           enter_cb;
        std::function<void ()>           leave_cb;
        std::function<void ()>           gain_focus_cb;
        std::function<void ()>           lose_focus_cb;
        std::function<void ()>           close_cb;

        void handle_event(const SDL_Event& event) const;

    friend class Main;
    };
}

#endif
