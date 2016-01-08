
#ifndef _PKZO_ENGINE_H_
#define _PKZO_ENGINE_H_

#include <string>
#include <vector>

#include "defines.h"
#include "Key.h"

namespace pkzo
{
    class Config;
    class Library;
    class Window;
    class Mouse;
    class Keyboard;
    class Joystick;
    class Screen;
    class ScreenRenderer;

    class PKZO_EXPORT Engine
    {
    public:

        Engine(const std::string& id);

        Engine(const Engine&) = delete;

        virtual ~Engine();

        const Engine& operator = (const Engine& ) = delete;

        const std::string& get_id() const;

        std::string get_id_slug() const;

        std::string get_config_folder() const;

        Config& get_config();

        const Config& get_config() const;

        Library& get_library();

        Window& get_window();

        const Window& get_window() const;

        Mouse& get_mouse();

        const Mouse& get_mouse() const;

        Keyboard& get_keyboard();

        const Keyboard& get_keyboard() const;

        unsigned int get_joystick_count() const;

        Joystick& get_joystick(unsigned int i);

        const Joystick& get_joystick(unsigned int i) const;

        bool has_screen();

        Screen& get_screen();

        const Screen& get_screen() const;

        void switch_screen(Screen* screen);

        bool is_running() const;

        void run();

        void stop();

    protected:
        
        virtual void on_draw();

        virtual void on_quit();

        virtual void on_mouse_press(unsigned int button, unsigned int x, unsigned int y);

        virtual void on_mouse_release(unsigned int button, unsigned int x, unsigned int y);

        virtual void on_mouse_move(unsigned int x, unsigned int y, int dx, int dy);

        virtual void on_key_press(Key key);

        virtual void on_key_release(Key key);

    private:
        std::string id;
        bool        running;

        Config*   config;
        Library*  library;

        Window*   window;
        Mouse*    mouse;
        Keyboard* keyboard;
        std::vector<Joystick*> joysticks;

        ScreenRenderer* screen_renderer;
        Screen*         screen;
        Screen*         next_screen;

        void route_events();
    };
}

#endif
