/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "Mouse.h"

#include <cassert>
#include <stdexcept>
#include <SDL.h>

namespace pkzo
{
    Mouse::Mouse() {}
    
    Mouse::~Mouse() {}

    void Mouse::on_move(std::function<void (rgm::ivec2, rgm::ivec2)> cb)
    {
        move_cb = cb;
    }

    void Mouse::on_button_press(std::function<void (unsigned int, rgm::ivec2)> cb)
    {
        button_press_cb = cb;
    }
    
    void Mouse::on_button_release(std::function<void (unsigned int, rgm::ivec2)> cb)
    {
        button_release_cb = cb;
    }   
    
    void Mouse::show_cursor()
    {
        SDL_ShowCursor(1);
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
        
    void Mouse::hide_cursor()
    {
        SDL_ShowCursor(0);
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
    
    bool Mouse::is_cursor_visible() const
    {
        return SDL_ShowCursor(-1) == 1;
    }
        
    bool Mouse::is_pressed(unsigned int button) const
    {
        return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button)) == SDL_BUTTON(button);
    }

    void Mouse::handle_event(SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                if (button_press_cb)
                {
                   rgm::ivec2 pos(event.button.x, event.button.y);
                    button_press_cb(event.button.button, pos);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (button_release_cb)
                {
                   rgm::ivec2 pos(event.button.x, event.button.y);
                    button_release_cb(event.button.button, pos);
                }
                break;
            case SDL_MOUSEMOTION:
                if (move_cb)
                {
                   rgm::ivec2 pos(event.motion.x, event.motion.y);
                   rgm::ivec2 mov(event.motion.xrel, event.motion.yrel);
                    move_cb(mov, pos);
                }
                break;
            default:
                throw std::logic_error("NOT WITH ME!");
        }
    }
}
