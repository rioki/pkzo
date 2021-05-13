//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "pch.h"
#include "ModelViewer.h"

#include "EditorScreen.h"

namespace mv
{
    ModelViewer::ModelViewer(int argc, char* argv[])
    : engine("pkzo-model-viewer")
    {
        using pkzo::map_to_screen;

        auto& window = engine.get_main_window();
        window.set_caption("Pkzo - Model Viewer");

        screen_renderer = std::make_unique<pkzo::ScreenRenderer>();
        screen = std::make_unique<EditorScreen>(window.get_size());

        window.on_draw([this] () {
            if (screen)
            {
                screen->draw(*screen_renderer);
            }
        });

        auto& mouse = engine.get_mouse();
        mouse.on_button_down([this, &window] (auto button, auto pos) {
            if (screen)
            {
                auto p = map_to_screen(window.get_size(), screen->get_size(), pos);
                screen->handle_mouse_button_down(button, p);
            }
        });
        mouse.on_button_up([this, &window] (auto button, auto pos) {
            if (screen)
            {
                auto p = map_to_screen(window.get_size(), screen->get_size(), pos);
                screen->handle_mouse_button_up(button, p);
            }
        });
        mouse.on_move([this, &window] (auto pos, auto mov) {
            if (screen)
            {
                auto p = map_to_screen(window.get_size(), screen->get_size(), pos);
                auto m = map_to_screen(window.get_size(), screen->get_size(), mov);
                screen->handle_mouse_move(p, m);
            }
        });

        auto& keyboard = engine.get_keyboard();
        keyboard.on_key_down([this] (auto mod, auto key) {
            if (screen)
            {
                screen->handle_key_down(mod, key);
            }
        });
        keyboard.on_key_up([this] (auto mod, auto key) {
            if (screen)
            {
                screen->handle_key_up(mod, key);
            }
        });
        keyboard.on_text([this] (auto text) {
            if (screen)
            {
                screen->handle_text(text);
            }
        });
    }

    ModelViewer::~ModelViewer() = default;

    int ModelViewer::run()
    {
        engine.run();
        return 0;
    }
}

int main(int argc, char* argv[])
{
    mv::ModelViewer app(argc, argv);
    return app.run();
}
