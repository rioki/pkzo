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

#include "pkzo.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "Keyboard.h"
#include "Mouse.h"

namespace pkzo
{
    bool is_init = false;
    std::function<void()> quit_cb;    

    void cleanup()
    {
        TTF_Quit();
        SDL_Quit();
    }

    void init()
    {
        if (is_init == false)
        {
            int r = SDL_Init(SDL_INIT_VIDEO);
            if (r != 0)
            {
                throw std::runtime_error(SDL_GetError());
            }

            r = TTF_Init();
            if (r != 0)
            {
                throw std::runtime_error(TTF_GetError());
            }

            std::atexit(cleanup);

            is_init = true;
        }
    }

    std::string get_version()
    {
        return PZKO_VERSION;
    }

    void route_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                if (quit_cb)
                {
                    quit_cb();
                }
                break;
            case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_TEXTINPUT:
                case SDL_TEXTEDITING:
                    for (Keyboard* keyboard : Keyboard::instances)
                    {
                        keyboard->handle_event(event);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                    for (Mouse* mouse : Mouse::instances)
                    {
                        mouse->handle_event(event);
                    }
                    break;
            default:
                // stfu
                break;
            }
        }
    }

    void on_quit(std::function<void()> cb)
    {
        quit_cb = cb;
    }
}