
#include "Engine.h"

#include <cassert>
#include <shlobj.h>

#include "path.h"
#include "fs.h"
#include "functions.h"
#include "Config.h"
#include "Window.h"
#include "Mouse.h"
#include "Keyboard.h"

namespace pkzo
{
    Engine::Engine(const std::string& i)
    : id(i), running(false), config(nullptr), window(nullptr), mouse(nullptr), keyboard(nullptr) 
    {           
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

        pkzo::on_quit([this] () {
            on_quit();
        });

        unsigned int dw, dh;
        std::tie(dw, dh) = Window::get_display_resolution();
        
        unsigned int w = config->get_value<unsigned int>("graphic", "width", dw);
        unsigned int h = config->get_value<unsigned int>("graphic", "height", dw);

        bool fs = config->get_value<bool>("graphic", "fullscreen", true);

        window = new Window(w, h, fs);
        window->set_title(id);

        mouse = new Mouse;
        mouse->on_button_press([this] (unsigned int button, unsigned int x, unsigned int y) {
            on_mouse_press(button, x, y);
        });
        mouse->on_button_release([this] (unsigned int button, unsigned int x, unsigned int y) {
            on_mouse_release(button, x, y);
        });
        mouse->on_move([this] (unsigned int x, unsigned int y, int dx, int dy) {
            on_mouse_move(x, y, dx, dy);
        });

        keyboard = new Keyboard;
        keyboard->on_key_press([this] (Key key) {
            on_key_press(key);
        });
        keyboard->on_key_release([this] (Key key) {
            on_key_release(key);
        });
    }

    Engine::~Engine() 
    {
        delete window;
        delete mouse;
        delete keyboard;
    }

    const std::string& Engine::get_id() const
    {
        return id;
    }

    // move to strex
    std::string slugify(const std::string& str)
    {
        std::string result;

        for (char c : str)
        {
            if (isalnum(c))
            {
                result.push_back(c);
            }
            else
            {
                result.push_back('-');
            }
        }

        return result;
    }

    std::string Engine::get_id_slug() const
    {
        return slugify(id);
    }

    std::string Engine::get_config_folder() const
    {
        char path[MAX_PATH];
        HRESULT r = SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path);
        
        return path::join(path, get_id_slug());
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

    bool Engine::is_running() const 
    {
        return running;
    }

    void Engine::run() 
    {
        running = true;
        while (running)
        {
            route_events();
            window->draw();
        }
    }

    void Engine::stop() 
    {
        running = false;
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
}
