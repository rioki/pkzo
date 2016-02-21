#include "MaterialEditor.h"

namespace pm
{
    MaterialEditor::MaterialEditor()
    : running(false), window(rgm::ivec2(800, 600), pkzo::Window::RESIZABLE), 
      canvas(window.get_size()), screen(window.get_size())
    {
        window.on_close([this] () {
            running = false;
        });
        window.on_draw([this] () {
            scene.draw(scene_renderer, window.get_aspect(), scene.get_camera());
            screen.draw(canvas);
        });
        window.on_resize([this] (rgm::ivec2 size) {
            screen.set_size(size);
        });

        // keyboard

        mouse.on_move([&] (rgm::ivec2 mov, rgm::ivec2 pos) {
            if (mouse.is_pressed(2))
            {
                scene.rotate_camera(mov);
            }

            screen.handle_mouse_move(mov, pos);
        });
        mouse.on_button_press([&] (unsigned int button, rgm::ivec2 pos) {
            screen.handle_mouse_press(button, pos);
        });
        mouse.on_button_release([&] (unsigned int button, rgm::ivec2 pos) {
            screen.handle_mouse_release(button, pos);
        });
    }

    MaterialEditor::~MaterialEditor() {}

    void MaterialEditor::run()
    {
        running = true;
        while (running)
        {
            pkzo::route_events();
            window.draw();
        }
    }
}