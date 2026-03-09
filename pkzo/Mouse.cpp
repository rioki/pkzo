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

#include "Mouse.h"

namespace pkzo
{
    std::vector<Mouse*> Mouse::instances;

    void Mouse::route_event(const SDL_Event& event)
    {
        if (event.type == SDL_EVENT_MOUSE_MOTION      ||
            event.type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
            event.type == SDL_EVENT_MOUSE_BUTTON_UP   ||
            event.type == SDL_EVENT_MOUSE_WHEEL   )
        {
            for (auto& instance : instances)
            {
                instance->handle_event(event);
            }
        }
    }

    Mouse::Mouse()
    {
         instances.push_back(this);
    }

    Mouse::~Mouse()
    {
        std::erase(instances, this);
    }

    rsig::connection Mouse::on_move(const std::function<void (MouseMoveEvent)>& handler)
    {
        return move_signal.connect(handler);
    }

    rsig::connection Mouse::on_button_down(const std::function<void (MouseButtonDownEvent)>& handler)
    {
        return button_down_signal.connect(handler);
    }

    rsig::connection Mouse::on_button_up(const std::function<void (MouseButtonUpEvent)>& handler)
    {
        return button_up_signal.connect(handler);
    }

    rsig::connection Mouse::on_wheel(const std::function<void (MouseWheelEvent)>& handler)
    {
        return wheel_signal.connect(handler);
    }

    void Mouse::handle_event(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_EVENT_MOUSE_MOTION:
                move_signal.emit({
                    .position  = glm::uvec2(event.motion.x, event.motion.y),
                    .releative = glm::ivec2(event.motion.xrel, event.motion.yrel)
                });
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                button_down_signal.emit({
                    .position = glm::uvec2(event.button.x, event.button.y),
                    .button   = static_cast<MouseButton>(event.button.button)
                });
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                button_up_signal.emit({
                    .position = glm::uvec2(event.button.x, event.button.y),
                    .button   = static_cast<MouseButton>(event.button.button)
                });
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                wheel_signal.emit({
                    .releative = glm::ivec2(event.wheel.x, event.wheel.y)
                });
                break;
            default:
                std::unreachable();
        }
    }
}
