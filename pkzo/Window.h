// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_WINDOW_H_
#define _PKZO_WINDOW_H_

#include <glm/glm.hpp>

#include "defines.h"
#include "EventEmitter.h"

typedef struct SDL_Window SDL_Window;
typedef void *SDL_GLContext;
union SDL_Event;

namespace pkzo
{
    /*!
     * The system window.
     */
    class PKZO_EXPORT Window : public EventEmitter
    {
    public:
        
        enum Mode
        {
            STATIC,            
            RESIZABLE,
            FULLSCREEN
        };

        /*!
         * Events emited by the window.
         */
        enum Event
        {
            DRAW,   //!< The qindow is being redrawn. void()
            RESIZE, //!< The qindow is being resized. void(uvec2 size)
            CLOSE   //!< The window is being closed. void()
        };

        Window(const glm::uvec2& size, Mode mode = STATIC, const std::string& title = "PKZO " PZKO_VERSION);

        Window(const Window&) = delete;

        ~Window();

        const Window& operator = (const Window&) = delete;

        /*!
         * Get the window's size.
         *
         * @return the window's size.
         */
        glm::uvec2 get_size() const;

        Mode get_mode() const;

        void set_title(const std::string& value);

        std::string get_title() const;

        void draw();
        
    private:
        SDL_Window*   window;
        SDL_GLContext glcontext;  
        
        Mode mode;  

        void handle_event(SDL_Event& event);
           
    friend class Engine;
    };
}

#endif
