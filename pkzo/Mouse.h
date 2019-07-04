// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_MOUSE_H_
#define _PKZO_MOUSE_H_

#include <functional>
#include <vector>
#include <glm/glm.hpp>

#include "defines.h"

union SDL_Event;

namespace pkzo
{
    class PKZO_EXPORT Mouse
    {
    public:
        Mouse();

        Mouse(const Mouse&) = delete;

        ~Mouse();

        const Mouse& operator = (const Mouse&) = delete;

        void on_move(std::function<void (glm::uvec2, glm::ivec2)> cb);

        void on_button_press(std::function<void (unsigned int, glm::uvec2)> cb);

        void on_button_release(std::function<void (unsigned int, glm::uvec2)> cb);

        void show_cursor();
    
        void hide_cursor();
        
        bool is_cursor_visible() const;    

        /**
         * Check if a mouse button is pressed.
         **/
        bool is_pressed(unsigned int button) const;

    private:
        static std::vector<Mouse*> instances;

        std::function<void (glm::uvec2, glm::ivec2)>   move_cb;
        std::function<void (unsigned int, glm::uvec2)> button_press_cb;
        std::function<void (unsigned int, glm::uvec2)> button_release_cb;

        void handle_event(SDL_Event& event);
        
		friend PKZO_EXPORT void route_events();
    };
}

#endif
