// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_KEYBOARD_H_
#define _PKZO_KEYBOARD_H_

#include <vector>
#include <functional>

#include "defines.h"
#include "Key.h"

union SDL_Event;

namespace pkzo
{
	class PKZO_EXPORT Keyboard
    {
    public:
        Keyboard(); 
        
        Keyboard(const Keyboard&) = delete;

        ~Keyboard();    

        const Keyboard& operator = (const Keyboard&) = delete;
    
        bool is_pressed(Key key) const;
    
        void on_key_press(std::function<void (Key)> cb);
        
        void on_key_release(std::function<void (Key)> cb);
        
        void on_text(std::function<void (std::string)> cb);
        
    private:
        static std::vector<Keyboard*> instances;
        
        std::function<void (Key)> key_press_cb;
        std::function<void (Key)> key_release_cb;
        std::function<void (std::string)> text_cb;
                
        void handle_event(SDL_Event& event);
        
		friend class Engine;
    };
}

#endif
