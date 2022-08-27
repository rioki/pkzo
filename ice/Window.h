// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <string>
#include <iostream>
#include <string_view>
#include <glm/glm.hpp>
#include <rsig/rsig.h>

#include "utils.h"
#include "SdlSentry.h"

struct SDL_Window;
typedef void *SDL_GLContext;

namespace ice
{
    enum class WindowMode
    {
        STATIC,
        RESIZABLE,
        FULLSCREEN,
        NATIVE_FULLSCREEN
    };

    ICE_SERIALIZE_ENUM(WindowMode, {
                                     {WindowMode::STATIC, "STATIC"},
                                     {WindowMode::RESIZABLE, "RESIZABLE"},
                                     {WindowMode::FULLSCREEN, "FULLSCREEN"},
                                     {WindowMode::NATIVE_FULLSCREEN, "NATIVE_FULLSCREEN"}
                                   });


    class ICE_EXPORT Window
    {
    public:
        Window(const glm::uvec2& size, WindowMode mode, const std::string_view caption);
        Window(const Window&) = delete;
        ~Window();
        Window& operator = (const Window&) = delete;

        void set_caption(const std::string_view text) noexcept;
        std::string get_caption() const noexcept;

        void resize(const glm::uvec2& size, WindowMode flags);
        glm::uvec2 get_size() const noexcept;
        WindowMode get_mode() const noexcept;

        rsig::signal<>& get_draw_sginal() noexcept;
        rsig::connection on_draw(const std::function<void ()>& cb) noexcept;

        void draw() const noexcept;

    private:
        SdlSentry     sdl_sentry;

        SDL_Window*   window    = nullptr;
        SDL_GLContext glcontext = nullptr;

        rsig::signal<> draw_signal;
    };
}
