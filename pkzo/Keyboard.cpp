// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Keyboard.h"

#include <algorithm>
#include <stdexcept>
#include <SDL2/SDL.h>

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
