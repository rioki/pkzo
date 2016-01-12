
#ifndef _PKZO_JOYSTICK_H_
#define _PKZO_JOYSTICK_H_

#include "EventEmitter.h"

union  SDL_Event;
struct _SDL_Joystick;
typedef struct _SDL_Joystick SDL_Joystick;

namespace pkzo
{
    enum HatPosition
    {
        HAT_CENTERED  = 0x00,
        HAT_UP        = 0x01,
        HAT_RIGHT     = 0x02,   
        HAT_DOWN      = 0x04,
        HAT_LEFT      = 0x08,
        HAT_RIGHTUP   = (0x02|0x01),
        HAT_RIGHTDOWN = (0x02|0x04),
        HAT_LEFTUP    = (0x08|0x01),
        HAT_LEFTDOWN  = (0x08|0x04)
    };

	class PKZO_EXPORT Joystick : public EventEmitter
    {
    public:
        
        enum Events
        {
            AXIS_MOVE,
            BUTTON_PRESS,
            BUTTON_RELEASE,
            HAT_MOVE,
            BALL_MOVE
        };
            
        std::string get_name() const;
        
        unsigned int get_axis_count() const;
        
        unsigned int get_button_count() const;
        
        unsigned int get_hat_count() const;
        
        unsigned int get_ball_count() const;
        
        float get_axis_position(unsigned int i) const;
        
        bool get_button_state(unsigned int i) const;
        
        HatPosition get_hat_position(unsigned int i) const;
        
    private:
        SDL_Joystick* handle;        
        
        Joystick(unsigned int id);        
        ~Joystick();
        
        void handle_event(SDL_Event& event);
        
    friend class Engine;
    };

    inline
    HatPosition operator | (HatPosition a, HatPosition b)
    {
        return (HatPosition)((unsigned int)a | (unsigned int)b);
    }

    inline
    HatPosition operator & (HatPosition a, HatPosition b)
    {
        return (HatPosition)((unsigned int)a & (unsigned int)b);
    }

    inline
    HatPosition operator ^ (HatPosition a, HatPosition b)
    {
        return (HatPosition)((unsigned int)a ^ (unsigned int)b);
    }
}

#endif
