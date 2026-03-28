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

#include "events.h"

#include <SDL3/SDL.h>

namespace pkzo
{
    auto quit_signal = rsig::signal<>{};
    auto input_singal = rsig::signal<const InputEvent&>{};

    rsig::connection on_quit(const std::function<void ()>& handler)
    {
        return quit_signal.connect(handler);
    }

    rsig::connection on_input(const std::function<void (const InputEvent& event)>& handler)
    {
        return input_singal.connect(handler);
    }

    void route_events()
    {
        // We assume that some other object pulled up SDL, e.g. Window.
        // Else a call to route_events is meaningless.

        auto event = SDL_Event{};
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    quit_signal.emit();
                    break;
                case SDL_EVENT_MOUSE_MOTION:
                    input_singal.emit(MouseMoveEvent{
                        .position  = glm::uvec2(event.motion.x, event.motion.y),
                        .releative = glm::ivec2(event.motion.xrel, event.motion.yrel)
                    });
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    input_singal.emit(MouseButtonDownEvent{
                        .position = glm::uvec2(event.button.x, event.button.y),
                        .button   = static_cast<MouseButton>(event.button.button)
                    });
                    break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    input_singal.emit(MouseButtonUpEvent{
                        .position = glm::uvec2(event.button.x, event.button.y),
                        .button   = static_cast<MouseButton>(event.button.button)
                    });
                    break;
                case SDL_EVENT_MOUSE_WHEEL:
                    input_singal.emit(MouseWheelEvent{
                        .releative = glm::ivec2(event.wheel.x, event.wheel.y)
                    });
                    break;
                case SDL_EVENT_KEY_DOWN:
                {
                    if (event.key.repeat == false)
                    {
                        input_singal.emit(KeyDownEvent{
                             .mod  = static_cast<KeyMod>(event.key.mod),
                             .key  = static_cast<KeyCode>(event.key.key),
                             .scan = static_cast<ScanCode>(event.key.scancode)
                        });
                    }
                    break;
                }
                case SDL_EVENT_KEY_UP:
                {
                    input_singal.emit(KeyUpEvent{
                             .mod  = static_cast<KeyMod>(event.key.mod),
                             .key  = static_cast<KeyCode>(event.key.key),
                             .scan = static_cast<ScanCode>(event.key.scancode)
                        });
                    break;
            }
            }
        }
    }
}
