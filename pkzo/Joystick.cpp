
#include "Joystick.h"

#include <SDL.h>
#include <stdexcept>

namespace pkzo
{            
    std::string Joystick::get_name() const
    {
        const char* name = SDL_JoystickName(handle);
        if (name == NULL)
        {
            throw std::runtime_error(SDL_GetError());
        }
        return name;
    }
    
    unsigned int Joystick::get_axis_count() const 
    {
        int i = SDL_JoystickNumAxes(handle);
        if (i < 0)
        {
            throw std::runtime_error(SDL_GetError());
        }
        return static_cast<unsigned int>(i);
    }
    
    unsigned int Joystick::get_button_count() const 
    {
        int i = SDL_JoystickNumButtons(handle);
        if (i < 0)
        {
            throw std::runtime_error(SDL_GetError());
        }
        return static_cast<unsigned int>(i);
    }
    
    unsigned int Joystick::get_hat_count() const 
    {
        int i = SDL_JoystickNumHats(handle);
        if (i < 0)
        {
            throw std::runtime_error(SDL_GetError());
        }
        return static_cast<unsigned int>(i);
    }
    
    unsigned int Joystick::get_ball_count() const 
    {
        int i = SDL_JoystickNumBalls(handle);
        if (i < 0)
        {
            throw std::runtime_error(SDL_GetError());
        }
        return static_cast<unsigned int>(i);
    }
    
    float Joystick::get_axis_position(unsigned int i) const 
    {
        Sint16 v = SDL_JoystickGetAxis(handle, i);
        return static_cast<float>(v) / 32767.0f;
    }
    
    bool Joystick::get_button_state(unsigned int i) const 
    {
        Uint8 v = SDL_JoystickGetButton(handle, i);
        return v == 1;
    }   
    
    
    HatPosition Joystick::get_hat_position(unsigned int i) const 
    {
        Uint8 v = SDL_JoystickGetHat(handle, i);
        return static_cast<HatPosition>(v);
    }
    
    void Joystick::on_axis_move(std::function<void (unsigned int, float)> cb) 
    {
        axis_move_cb = cb;
    }
    
    void Joystick::on_button_press(std::function<void (unsigned int)> cb) 
    {
        button_press_cb = cb;
    }
    
    void Joystick::on_button_release(std::function<void (unsigned int)> cb) 
    {
        button_release_cb = cb;
    }
    
    void Joystick::on_hat_move(std::function<void (unsigned int, HatPosition)> cb) 
    {
        hat_move_cb = cb;
    }
    
    void Joystick::on_ball_move(std::function<void (unsigned int, int, int)> cb) 
    {
        ball_move_cb = cb;
    }    
    
    Joystick::Joystick(unsigned int id) 
    : handle(NULL)
    {
        handle = SDL_JoystickOpen(id);
        if (handle == NULL)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }
    
    Joystick::~Joystick() 
    {
        SDL_JoystickClose(handle);
    }
    
    void Joystick::handle_event(SDL_Event& event) 
    {

        SDL_JoystickID me = SDL_JoystickInstanceID(handle);
        switch (event.type)
        {
            case SDL_JOYAXISMOTION:
                if (me == event.jaxis.which && axis_move_cb)
                {
                    axis_move_cb(event.jaxis.axis, static_cast<float>(event.jaxis.value) / 32767.0f);
                }
                break;
            case SDL_JOYBALLMOTION:
                if (me == event.jball.which && ball_move_cb)
                {
                    ball_move_cb(event.jball.ball, event.jball.xrel, event.jball.yrel);
                }
                break;
            case SDL_JOYHATMOTION:            
                if (me == event.jhat.which && hat_move_cb)
                {
                    hat_move_cb(event.jhat.hat, static_cast<HatPosition>(event.jhat.value));
                }
                break;
            case SDL_JOYBUTTONDOWN:
                if (me == event.jbutton.which && button_press_cb)
                {
                    button_press_cb(event.jbutton.button);
                }
                break;
            case SDL_JOYBUTTONUP:
            {
                if (me == event.jbutton.which && button_release_cb)
                {
                    button_release_cb(event.jbutton.button);
                }
                break;
            }
            default:
                throw std::logic_error("Joystick does not handle this type of event.");
        }
    }
}
