// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_WINDOW_H_
#define _PKZO_WINDOW_H_

#include <functional>
#include <vector>
#include <glm/glm.hpp>

#include "defines.h"
#include "SDLSentry.h"

typedef struct SDL_Window SDL_Window;
typedef void *SDL_GLContext;
union SDL_Event;

namespace pkzo
{
    class PKZO_EXPORT Window
    {
    public:
        
        enum Mode
        {
            STATIC,            
            RESIZABLE,
            FULLSCREEN
        };

        Window(const glm::uvec2& size, Mode mode = STATIC, const std::string& title = "PKZO " PZKO_VERSION);

        Window(const Window&) = delete;

        ~Window();

        const Window& operator = (const Window&) = delete;

        glm::uvec2 get_size() const;

        Mode get_mode() const;

        void set_title(const std::string& value);

        std::string get_title() const;

        void on_draw(std::function<void ()> cb);

        void on_resize(std::function<void (unsigned int, unsigned int)> cb);

        void on_close(std::function<void ()> cb);

        void draw();
        
    private:
        static std::vector<Window*> instances;

        SDLSentry sdl_sentry;

        SDL_Window*   window;
        SDL_GLContext glcontext;  
        
        Mode mode;  

        std::function<void ()>                           draw_cb; 
        std::function<void (unsigned int, unsigned int)> resize_cb;
        std::function<void ()>                           close_cb;

        void handle_event(SDL_Event& event);
           
    friend PKZO_EXPORT void route_events();
    };
}

#endif
