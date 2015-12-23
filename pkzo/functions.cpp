
#include "pkzo.h"

#include <SDL.h>

#include "Keyboard.h"
#include "Mouse.h"

namespace pkzo
{
    bool is_init = false;
    std::function<void()> quit_cb;    

    void cleanup()
    {
        SDL_Quit();
    }

    void init()
    {
        if (is_init == false)
        {
            int r = SDL_Init(SDL_INIT_VIDEO);
            if (r != 0)
            {
                throw std::runtime_error(SDL_GetError());
            }

            std::atexit(cleanup);

            is_init = true;
        }
    }

    std::string get_version()
    {
        return PZKO_VERSION;
    }

    void route_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                if (quit_cb)
                {
                    quit_cb();
                }
                break;
            case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_TEXTINPUT:
                case SDL_TEXTEDITING:
                    for (Keyboard* keyboard : Keyboard::instances)
                    {
                        keyboard->handle_event(event);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                    for (Mouse* mouse : Mouse::instances)
                    {
                        mouse->handle_event(event);
                    }
                    break;
            default:
                // stfu
                break;
            }
        }
    }

    void on_quit(std::function<void()> cb)
    {
        quit_cb = cb;
    }
}