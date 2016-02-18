
#include "pkzo.h"

#include <SDL.h>

namespace pkzo
{
    void route_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
             switch (event.type)
             {
                case SDL_QUIT:
                case SDL_WINDOWEVENT:
                // TODO other window events
                    for (Window* window : Window::instances)
                    {
                        window->handle_event(event);
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
                    /* stfu */
                    break;
             }
        }
    }
}    
