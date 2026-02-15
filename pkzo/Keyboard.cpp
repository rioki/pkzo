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

#include "Keyboard.h"

namespace pkzo
{
    std::vector<Keyboard*> Keyboard::instances;

    void Keyboard::route_event(const SDL_Event& event)
    {
        if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP)
        {
            for (auto& instance : instances)
            {
                instance->handle_event(event);
            }
        }
    }

    Keyboard::Keyboard()
    {
         instances.push_back(this);
    }

    Keyboard::~Keyboard()
    {
        std::erase(instances, this);
    }

    rsig::connection Keyboard::on_key_down(const std::function<void (KeyMod, KeyCode, ScanCode)>& handler)
    {
        return key_down_signal.connect(handler);
    }

    rsig::connection Keyboard::on_key_up(const std::function<void (KeyMod, KeyCode, ScanCode)>& handler)
    {
        return key_up_signal.connect(handler);
    }

    void Keyboard::handle_event(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_EVENT_KEY_DOWN:
            {
                if (event.key.repeat == false)
                {
                    auto mod  = static_cast<KeyMod>(event.key.mod);
                    auto key  = static_cast<KeyCode>(event.key.key);
                    auto scan = static_cast<ScanCode>(event.key.scancode);
                    key_down_signal.emit(mod, key, scan);
                }
                break;
            }
            case SDL_EVENT_KEY_UP:
            {
                auto mod  = static_cast<KeyMod>(event.key.mod);
                auto key  = static_cast<KeyCode>(event.key.key);
                auto scan = static_cast<ScanCode>(event.key.scancode);
                key_up_signal.emit(mod, key, scan);
                break;
            }
            default:
                std::unreachable();
        }
    }
}
