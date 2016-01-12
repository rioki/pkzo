
#ifndef _PKZO_ENGINE_H_
#define _PKZO_ENGINE_H_

#include <string>
#include <vector>
#include <ctime>

#include "defines.h"
#include "Key.h"
#include "EventEmitter.h"

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
    class Scene;
    class SceneRenderer;

    class PKZO_EXPORT Engine : public EventEmitter
    {
    public:

        enum Events
        {
            TICK,
            CHANGE_SCENE,
            CHANGE_SCREEN,
        };

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

        bool has_screen() const;

        Screen& get_screen();

        const Screen& get_screen() const;

        void switch_screen(Screen* screen);

        bool has_scene() const;

        Scene& get_scene();

        const Scene& get_scene() const;

        void switch_scene(Scene* scene);

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

        clock_t         last_frame;

        ScreenRenderer* screen_renderer;
        Screen*         screen;
        Screen*         next_screen;

        SceneRenderer*  scene_renderer;
        Scene*          scene;
        Scene*          next_scene;

        void route_events();
    };
}

#endif
