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

#include "dialogs.h"

#include <SDL3/SDL_messagebox.h>

namespace pkzo
{
    SDL_MessageBoxFlags get_flags(Icon icon)
    {
        switch (icon)
        {
            case Icon::INFORMATION: return SDL_MESSAGEBOX_INFORMATION;
            case Icon::WARNING:     return SDL_MESSAGEBOX_WARNING;
            case Icon::ERROR:       return SDL_MESSAGEBOX_ERROR;
            default:                std::unreachable();
        }
    };

    std::vector<SDL_MessageBoxButtonData> make_buttons(Button buttons)
    {
        auto sdl_buttons = std::vector<SDL_MessageBoxButtonData>();

        switch (buttons)
        {
            case Button::OK:
            {
                sdl_buttons.emplace_back(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, std::to_underlying(Button::OK), "OK");
                break;
            }
            case Button::YES|Button::NO:
            {
                sdl_buttons.emplace_back(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, std::to_underlying(Button::YES), "Yes");
                sdl_buttons.emplace_back(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, std::to_underlying(Button::NO), "No");
                break;
            }
            case Button::CONTINUE|Button::ABORT:
            {
                sdl_buttons.emplace_back(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, std::to_underlying(Button::CONTINUE), "Continue");
                sdl_buttons.emplace_back(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, std::to_underlying(Button::ABORT), "Abort");
                break;
            }
            default:
                throw std::logic_error("Unexpected button config.");
        }

        return sdl_buttons;
    }

    Button show_message_box(const std::string_view title, const std::string_view message, Icon icon, Button buttons)
    {
        const auto sdl_buttons = make_buttons(buttons);

        auto specs = SDL_MessageBoxData {
            .flags      = get_flags(icon),
            .window     = nullptr,
            .title      = title.data(),
            .message    = message.data(),
            .numbuttons = static_cast<int>(sdl_buttons.size()),
            .buttons    = sdl_buttons.data()
        };

        int result_button = 0;
        auto result = SDL_ShowMessageBox(&specs, &result_button);
        if (result == false)
        {
            throw std::runtime_error("Failed to show message box");
        }

        return static_cast<Button>(result_button);
    }
}