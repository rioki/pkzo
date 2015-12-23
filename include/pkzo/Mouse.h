
#ifndef _PKZO_MOUSE_H_
#define _PKZO_MOUSE_H_

#include <vector>
#include <functional>

#include "defines.h"

union SDL_Event;

namespace pkzo
{
	class PKZO_EXPORT Mouse
    {
    public:
        
        Mouse(); 
        
        ~Mouse();
        
        bool is_pressed(unsigned int button) const;

        std::tuple<unsigned int, unsigned int> get_cursor() const;

        void on_button_press(std::function<void (unsigned int, unsigned int, unsigned int)> cb);
        
        void on_button_release(std::function<void (unsigned int, unsigned int, unsigned int)> cb);
        
        void on_move(std::function<void (unsigned int, unsigned int, int, int)> cb);
        
        void show_cursor();
        
        void hide_cursor();
        
        bool is_cursor_visible() const;
        
    private:        
        static std::vector<Mouse*> instances;
        
        std::function<void (unsigned int, unsigned int, unsigned int)> button_press_cb;        
        std::function<void (unsigned int, unsigned int, unsigned int)> button_release_cb;        
        std::function<void (unsigned int, unsigned int, int, int)> move_cb;
        
        void handle_event(SDL_Event& event);
        
		friend PKZO_EXPORT void route_events();
    };
}

#endif
