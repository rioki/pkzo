/*
  pkzo

  Copyright (c) 2014-2018 Sean Farrell

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

#include "Keyboard.h"

#include <algorithm>
#include <stdexcept>
#include <SDL.h>

namespace pkzo
{    
    std::vector<Keyboard*> Keyboard::instances;

    Keyboard::Keyboard() 
    {    
        if (instances.size() == 0)
        {
            SDL_StartTextInput();    
        }
        instances.push_back(this);
    }
    
    Keyboard::~Keyboard() 
    {
        if (instances.size() == 0)
        {
            SDL_StopTextInput();
        }
        auto i = std::find(instances.begin(), instances.end(), this);
        if (i != instances.end())
        {
            instances.erase(i);
        }
    }
    
    bool Keyboard::is_pressed(Key key) const
    {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        return state[key] == 1;
    }

    void Keyboard::on_key_press(std::function<void (Key)> cb)
    {
        key_press_cb = cb;
    }
    
    void Keyboard::on_key_release(std::function<void (Key)> cb)
    {
        key_release_cb = cb;
    }
    
    void Keyboard::on_text(std::function<void (std::string)> cb)
    {
        text_cb = cb;
    }

    void Keyboard::handle_event(SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (key_press_cb)
                {
                    key_press_cb(static_cast<Key>(event.key.keysym.scancode));
                }
                break;
            case SDL_KEYUP:
                if (key_release_cb)
                {
                    key_release_cb(static_cast<Key>(event.key.keysym.scancode));
                }
                break;
            case SDL_TEXTINPUT:
                if (text_cb)
                {
                    text_cb(event.text.text);
                }
                break;
            case SDL_TEXTEDITING:
                // handled by window
                break;
            default:
                throw std::logic_error("ARE YOU INSANE!");
        }
    }     
}
