//
// pkzo
// 
// Copyright 2015 Sean Farrell
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 

#include "Mouse.h"

#include <SDL.h>

namespace pkzo
{        
    Mouse::Mouse() {}
    
    Mouse::~Mouse() {}

    bool Mouse::is_pressed(unsigned int button) const
    {
        return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button)) == SDL_BUTTON(button);
    }

    std::tuple<unsigned int, unsigned int> Mouse::get_cursor() const
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        return std::make_tuple(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
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
        
    void Mouse::handle_event(SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                emit<unsigned int, unsigned int, unsigned int>(BUTTON_PRESS, event.button.button, event.button.x, event.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                emit<unsigned int, unsigned int, unsigned int>(BUTTON_RELEASE, event.button.button, event.button.x, event.button.y);
                break;
            case SDL_MOUSEMOTION:
                emit<unsigned int, unsigned int, int, int>(MOVE, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                break;
            default:
                throw std::logic_error("NOT WITH ME!");
        }
    }
}
