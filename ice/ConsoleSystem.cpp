// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"
#include "ConsoleSystem.h"

#include "utils.h"
#include "glm_2d.h"
#include "Engine.h"
#include "Settings.h"
#include "Font.h"
#include "Screen.h"
#include "Rectangle.h"
#include "Text.h"
#include "GraphicSystem.h"
#include "Keyboard.h"

namespace ice
{
    class ConsoleSystem::ConsoleScreen : public ice::Screen
    {
    public:
        ConsoleScreen(const glm::vec2 size, const std::shared_ptr<Font>& console_font, const glm::vec4& text_color, const glm::vec4& background_color, size_t lines = 5)
        : Screen(size),
          output_background(glm::mat3(1.0f), size, background_color),
          output_lines(lines),
          input_background(glm::mat3(1.0f), size, glm::mix(background_color, text_color, 0.05f)),
          input_line(glm::mat3(1.0f), "|", console_font, text_color)
        {
            assert(console_font);
            add_node(output_background);
            for (auto i = 0; i < output_lines.size(); i++)
            {
                output_lines[i] = std::make_unique<Text>(glm::mat3(1.0f), "", console_font, text_color);
                add_node(*output_lines[i]);
            }
            add_node(input_background);
            add_node(input_line);
            layout();
        };

        void set_output(const std::deque<std::string>& buffer)
        {
            assert(buffer.size() <= output_lines.size());
            auto i = 0u;
            for (const auto& text :  buffer)
            {
                output_lines[i]->set_text(text);
                i++;
            }

            layout();
        }

        void set_input(const std::string& text)
        {
            input_line.set_text(text + "|");
            layout();
        }

    private:
        // This may be replace by UI components later; but for now this will do.
        Rectangle                          output_background;
        std::vector<std::unique_ptr<Text>> output_lines;
        Rectangle                          input_background;
        Text                               input_line;

        void layout()
        {
            const auto& font = input_line.get_font();
            assert(font);
            auto em = static_cast<float>(font->estimate("M").y);
            auto hs = get_size() / 2.0f;

            auto top_left = glm::vec2(-hs.x, hs.y) + glm::vec2(em, -em);

            auto lines_count = static_cast<float>(output_lines.size());

            output_background.set_size({get_size().x - 2.0f * em, lines_count * 2.0f * em});
            output_background.set_transform(glm::translate(glm::mat3(1.0f), {0.0f, top_left.y - lines_count * em}));

            auto pos = top_left;
            for (const auto& line : output_lines)
            {
                line->set_transform(glm::translate(glm::mat3(1.0f), glm::vec2(pos.x + line->get_size().x / 2.0f, pos.y - em)));
                pos.y -= 2.0f*em;
            }

            input_background.set_size({get_size().x - 2.0f * em, 2.0f * em});
            input_background.set_transform(glm::translate(glm::mat3(1.0f), {0.0f, top_left.y - (2.0f * lines_count + 1.0f) * em}));
            input_line.set_transform(glm::translate(glm::mat3(1.0f), glm::vec2(pos.x + input_line.get_size().x / 2.0f, pos.y - em)));
        }
    };

    ConsoleSystem::ConsoleSystem(ice::Engine& e) noexcept
    : System(e)
    {
        max_output_lines = engine.get_setting("ConsoleSystem", "lines",       max_output_lines);
        console_key      = engine.get_setting("ConsoleSystem", "console_key", console_key);

        if (auto keyboard = engine.get_keyboard())
        {
            keyboard->on_key_down([this] (auto mod, auto key) {
                if (key != console_key)
                {
                    return;
                }

                if (!is_visible())
                {
                    show();
                }
                else
                {
                    hide();
                }
            });
        }
    }

    ConsoleSystem::~ConsoleSystem()
    {
        hide(); // clean up any pending OpenGL resouces
        c9y::sync_point(); // actually execute hide
    }

    void ConsoleSystem::define(const std::string& name, const CommandFunc& func) noexcept
    {
        assert(func);
        assert(commands.find(name) == end(commands));

        commands[name] = func;
    }

    void ConsoleSystem::exec(const std::string& code)
    {
        auto bits = tokenize(code);

        if (!bits.empty())
        {
            auto i = commands.find(bits[0]);
            if (i != commands.end())
            {
                i->second(bits);
            }
            else
            {
                write(std::format("Unknown command {}.", bits[0]));
            }
        }
    }

    void ConsoleSystem::write(const std::string& line) noexcept
    {
        trace(line);
        output_buffer.push_back(line);
        if (output_buffer.size() > max_output_lines)
        {
            assert(output_buffer.size() == max_output_lines + 1);
            output_buffer.pop_front();
        }

        if (screen)
        {
            screen->set_output(output_buffer);
        }
    }

    void ConsoleSystem::show()
    {
        if (!visible)
        {
            assert(screen == nullptr);
            c9y::sync([this] () {
                auto gs = engine.get_system<GraphicSystem>();
                if (!gs)
                {
                    trace("Can't show console, no graphic system loaded.");
                    return;
                }

                const auto size = gs->get_window_size();

                auto font_file        = engine.get_setting("ConsoleSystem", "font",             "fonts/DejaVuSansMono.ttf");
                auto font_size        = engine.get_setting("ConsoleSystem", "font_size",        18u);
                auto text_color       = engine.get_setting("ConsoleSystem", "text_color",       rgba(0xc2d9ffff));
                auto background_color = engine.get_setting("ConsoleSystem", "background_color", rgba(0x101112c4));
                auto lines            = engine.get_setting("ConsoleSystem", "lines",            5u);

                auto font = engine.load_asset<ice::Font>(font_file, font_size);

                screen = std::make_unique<ConsoleScreen>(size, font, text_color, background_color, lines);
                screen->set_output(output_buffer);
                screen->set_engine(&engine);

                render_event = gs->debug_draw([this] () {
                    screen->draw();
                });

                if (auto keyboard = engine.get_keyboard())
                {
                    text_event = keyboard->on_text([this] (auto text) {
                        assert(screen);

                        input_buffer += text;
                        screen->set_input(input_buffer);
                    });
                    key_event = keyboard->on_key_down([this] (auto mod, auto key) {
                        assert(screen);

                        if (ice::KeyMod::NONE == mod)
                        {
                            switch (key)
                            {
                                case ice::Key::RETURN:
                                case ice::Key::KPENTER:
                                    exec(input_buffer);
                                    input_buffer.clear();
                                    screen->set_input(input_buffer);
                                    break;
                                case ice::Key::BACKSPACE:
                                    if (!input_buffer.empty())
                                    {
                                        input_buffer.pop_back();
                                    }
                                    screen->set_input(input_buffer);
                                    break;
                                default:
                                    // don't care about other input
                                    break;
                            }
                        }
                    });
                }
                else
                {
                     trace("Can't listen to input, no input system loaded.");
                }

                visible = true;
            });
        }
    }

    void ConsoleSystem::hide()
    {
        if (visible)
        {
            c9y::sync([this] () {
                if (auto keyboard = engine.get_keyboard())
                {
                    keyboard->get_text_signal().disconnect(text_event);
                    keyboard->get_key_down_signal().disconnect(key_event);
                }

                auto gs = engine.get_system<GraphicSystem>();
                assert(gs);
                gs->get_debug_draw_signal().disconnect(render_event);

                screen->set_engine(nullptr);
                screen = nullptr;
                visible = false;
            });
        }
    }

    bool ConsoleSystem::is_visible() const noexcept
    {
        return visible;
    }
}


