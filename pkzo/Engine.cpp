
#include "Engine.h"

#include <cassert>
#include <shlobj.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "path.h"
#include "fs.h"
#include "strex.h"
#include "Config.h"
#include "Library.h"
#include "Window.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Joystick.h"
#include "Screen.h"
#include "ScreenRenderer.h"
#include "Scene.h"
#include "SceneRenderer.h"

namespace pkzo
{
    Engine::Engine(const std::string& i)
    : id(i), running(false), config(nullptr), window(nullptr), mouse(nullptr), keyboard(nullptr),
      screen_renderer(nullptr), screen(nullptr), next_screen(nullptr),
      scene_renderer(nullptr), scene(nullptr), next_scene(nullptr)
    {           
        int r = SDL_Init(SDL_INIT_VIDEO);
        if (r != 0)
        {
            throw std::runtime_error(SDL_GetError());
        }
        r = TTF_Init();
        if (r != 0)
        {
            throw std::runtime_error(TTF_GetError());
        }
        
        config = new Config;
        
        std::string config_file = path::join(get_config_folder(), "Config.cfg"); 
        // load from CWD for debug purposes
        if (fs::exists("Config.cfg"))
        {
            config->load("Config.cfg");
        }
        else if (fs::exists(config_file))
        {
            config->load(config_file);
        }

        library = new Library;

        unsigned int dw, dh;
        std::tie(dw, dh) = Window::get_display_resolution();
        
        unsigned int w = config->get_value<unsigned int>("graphic", "width", dw);
        unsigned int h = config->get_value<unsigned int>("graphic", "height", dw);

        bool fs = config->get_value<bool>("graphic", "fullscreen", true);

        window = new Window(w, h, fs);
        window->set_title(id);
        window->on_draw([this] () {
            on_draw();
        });

        screen_renderer = new ScreenRenderer;
        scene_renderer  = new SceneRenderer;

        // REVIEW: The event routing, should be engine -> screen -> mouse/keyboard/joystick

        mouse = new Mouse;
        mouse->on(Mouse::BUTTON_PRESS, [this] (unsigned int button, unsigned int x, unsigned int y) {
            on_mouse_press(button, x, y);
        });
        mouse->on(Mouse::BUTTON_RELEASE, [this] (unsigned int button, unsigned int x, unsigned int y) {
            on_mouse_release(button, x, y);
        });
        mouse->on(Mouse::MOVE, [this] (unsigned int x, unsigned int y, int dx, int dy) {
            on_mouse_move(x, y, dx, dy);
        });

        keyboard = new Keyboard;
        keyboard->on(Keyboard::KEY_PRESS, [this] (Key key) {
            on_key_press(key);
        });
        keyboard->on(Keyboard::KEY_RELEASE, [this] (Key key) {
            on_key_release(key);
        });

        int numj = SDL_NumJoysticks();
        joysticks.resize(numj);
        for (int i = 0; i < numj; i++)
        {
            joysticks[i] = new Joystick(i);
        }
    }

    Engine::~Engine() 
    {
        delete window;
        delete mouse;
        delete keyboard;

        TTF_Quit();
        SDL_Quit();
    }

    const std::string& Engine::get_id() const
    {
        return id;
    }

    std::string Engine::get_id_slug() const
    {
        return strex::slugify(id);
    }

    std::string Engine::get_config_folder() const
    {
        wchar_t path[MAX_PATH];
        HRESULT r = SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path);
        
        return path::join(strex::narrow(path), get_id_slug());
    }

    Config& Engine::get_config()
    {
        assert(config != nullptr);
        return *config;
    }

    const Config& Engine::get_config() const
    {
        assert(config != nullptr);
        return *config;
    }

    Library& Engine::get_library()
    {
        assert(library != nullptr);
        return *library;
    }

    Window& Engine::get_window()
    {
        assert(window != nullptr);
        return *window;
    }

    const Window& Engine::get_window() const
    {
        assert(window != nullptr);
        return *window;
    }

    Mouse& Engine::get_mouse()
    {
        assert(mouse != nullptr);
        return *mouse;
    }

    const Mouse& Engine::get_mouse() const
    {
        assert(mouse != nullptr);
        return *mouse;
    }

    Keyboard& Engine::get_keyboard()
    {
        assert(keyboard != nullptr);
        return *keyboard;
    }

    const Keyboard& Engine::get_keyboard() const
    {
        assert(keyboard != nullptr);
        return *keyboard;
    }

    unsigned int Engine::get_joystick_count() const
    {
        return (unsigned int)joysticks.size();
    }

    Joystick& Engine::get_joystick(unsigned int i)
    {            
        assert(i < joysticks.size());
        assert(joysticks[i] != nullptr);
        return *joysticks[i];
    }

    const Joystick& Engine::get_joystick(unsigned int i) const
    {
        assert(i < joysticks.size());
        assert(joysticks[i] != nullptr);
        return *joysticks[i];
    }

    bool Engine::has_screen() const
    {
        return screen != nullptr;
    }

    Screen& Engine::get_screen()
    {
        assert(screen != nullptr);
        return *screen;
    }

    const Screen& Engine::get_screen() const
    {
        assert(screen != nullptr);
        return *screen;
    }

    void Engine::switch_screen(Screen* ns)
    {
        assert(next_screen == nullptr);
        next_screen = ns;
    }

    bool Engine::has_scene() const
    {
        return scene != nullptr;
    }

    Scene& Engine::get_scene()
    {
        assert(scene != nullptr);
        return *scene;
    }

    const Scene& Engine::get_scene() const
    {
        assert(scene != nullptr);
        return *scene;
    }

    void Engine::switch_scene(Scene* ns)
    {
        assert(next_scene == nullptr);
        next_scene = ns;
    }

    bool Engine::is_running() const 
    {
        return running;
    }

    void Engine::run() 
    {
        last_frame = std::clock();

        running = true;
        while (running)
        {
            if (next_screen)
            {
                delete screen;
                screen = next_screen;
                next_screen = nullptr;
                emit(CHANGE_SCREEN);
            }

            if (next_scene)
            {
                delete scene;
                scene = next_scene;
                next_scene = nullptr;
                emit(CHANGE_SCENE);
            }

            route_events();

            clock_t now = std::clock();;
            float t  = (float)now / (float)CLOCKS_PER_SEC;
            float dt = (float)(now - last_frame) / (float)CLOCKS_PER_SEC;

            emit<float, float>(TICK, t, dt);

            if (scene)
            {
                scene->update(t, dt);
            }


            window->draw();
        }
    }

    void Engine::stop() 
    {
        running = false;
    }    

    void Engine::on_draw()
    {
        if (scene)
        {
            scene->render(*scene_renderer);
        }

        if (screen) 
        {
            screen->draw(*screen_renderer);
        }
    }

    void Engine::on_quit()
    {
        stop();
    }

    void Engine::on_mouse_press(unsigned int button, unsigned int x, unsigned int y) {}

    void Engine::on_mouse_release(unsigned int button, unsigned int x, unsigned int y) {}

    void Engine::on_mouse_move(unsigned int x, unsigned int y, int dx, int dy) {}

    void Engine::on_key_press(Key key)
    {
        if (key == KEY_ESCAPE)
        {
            stop();
        }
    }

    void Engine::on_key_release(Key key) {}

    void Engine::route_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    on_quit();
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_TEXTINPUT:
                case SDL_TEXTEDITING:
                    assert(keyboard != nullptr);
                    keyboard->handle_event(event);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                    assert(mouse != nullptr);
                    mouse->handle_event(event);
                    break;
                case SDL_JOYAXISMOTION:
                case SDL_JOYBALLMOTION:   
                case SDL_JOYHATMOTION:
                case SDL_JOYBUTTONDOWN:
                case SDL_JOYBUTTONUP:
                {
                    for (Joystick* joystick : joysticks)
                    {
                        joystick->handle_event(event);
                    }
                    break;
                }
            default:
                // stfu
                break;
            }
        }
    }
}
