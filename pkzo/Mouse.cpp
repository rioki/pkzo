// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "Mouse.h"

#include <cassert>
#include <stdexcept>
#include <SDL2/SDL.h>

namespace pkzo
{
    std::vector<Mouse*> Mouse::instances;

    Mouse::Mouse() 
    {
        instances.push_back(this);
    }
    
    Mouse::~Mouse() 
    {
        auto i = std::find(instances.begin(), instances.end(), this);
        assert(i != instances.end());
        instances.erase(i);        
    }

    void Mouse::on_move(std::function<void (glm::uvec2, glm::ivec2)> cb)
    {
        move_cb = cb;
    }

    void Mouse::on_button_press(std::function<void (unsigned int, glm::uvec2)> cb)
    {
        button_press_cb = cb;
    }
    
    void Mouse::on_button_release(std::function<void (unsigned int, glm::uvec2)> cb)
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
                    button_press_cb(event.button.button, glm::uvec2(event.button.x, event.button.y));
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (button_release_cb)
                {
                    button_release_cb(event.button.button, glm::uvec2(event.button.x, event.button.y));
                }
                break;
            case SDL_MOUSEMOTION:
                if (move_cb)
                {
                    move_cb(glm::uvec2(event.motion.x, event.motion.y), glm::ivec2(event.motion.xrel, event.motion.yrel));
                }
                break;
            default:
                throw std::logic_error("NOT WITH ME!");
        }
    }
}
