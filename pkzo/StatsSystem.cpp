// pkzo
// Copyright 2022-2023 Sean Farrell
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
#include "StatsSystem.h"

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

namespace pkzo
{
    using fsec = std::chrono::duration<float>;

    class StatsSystem::StatsScreen : public pkzo::Screen
    {
    public:
        StatsScreen(const glm::vec2 size, const std::shared_ptr<Font>& _font, const glm::vec4& _text_color, const glm::vec4& background_color)
        : Screen(size), font(_font), text_color(_text_color)
        {
            assert(font);
            background = std::make_shared<Rectangle>(glm::mat3(1.0f), glm::vec2(15.0f), background_color);
            add_node(background);
        };

        void set_stats(const std::map<std::string, Stat>& stats)
        {
            // for we will create and destroy each time the values,
            // this if inefficient, but for now it will do

            // remove old widgets
            for (const auto& text : labels)
            {
                remove_node(text);
            }
            for (const auto& text : values)
            {
                remove_node(text);
            }
            labels.clear();
            values.clear();

            // add new widgets
            for (const auto& [name, stat] : stats)
            {
                auto label_text = std::make_shared<Text>(glm::mat3(1.0f), name, font, text_color);
                add_node(label_text);
                labels.push_back(label_text);

                auto value_text = std::make_shared<Text>(glm::mat3(1.0f), std::format("{:8.3f}", stat.value), font, text_color);
                add_node(value_text);
                values.push_back(value_text);
            }

            // layout widgets
            auto em    = static_cast<float>(font->estimate("M").y);
            auto padding = 0.5f * em;
            auto size  = get_size();
            auto hsize = size / 2.0f;

            auto max_labels_width = std::accumulate(begin(labels), end(labels), 0.0f, [] (const auto& max_width, const auto& text) {
                return std::max(max_width, text->get_size().x);
            });
            auto max_values_width = std::accumulate(begin(values), end(values), 0.0f, [] (const auto& max_width, const auto& text) {
                return std::max(max_width, text->get_size().x);
            });

            auto top_right = glm::vec2(hsize.x - padding, hsize.y - padding);
            auto top_left  = glm::vec2(top_right.x - max_labels_width - max_values_width - 3.0f * padding, top_right.y);
            auto label_start = top_left + glm::vec2(padding, -padding);
            auto value_start = label_start + glm::vec2(max_labels_width, 0.0f) + glm::vec2(padding, 0.0f);

            auto pos = label_start;
            for (const auto& text : labels)
            {
                text->set_transform(glm::translate(glm::mat3(1.0f), glm::vec2(pos.x + text->get_size().x / 2.0f, pos.y - em)));
                pos.y -= em + padding;
            }

            pos = value_start;
            for (const auto& text : values)
            {
                text->set_transform(glm::translate(glm::mat3(1.0f), glm::vec2(pos.x + text->get_size().x / 2.0f, pos.y - em)));
                pos.y -= em + padding;
            }

            auto bottom_left  = glm::vec2(top_left.x, pos.y - padding);
            auto bottom_right = glm::vec2(top_right.x, bottom_left.y);

            auto bsize = top_right - bottom_left;
            background->set_size(bsize);
            background->set_transform(glm::translate(glm::mat3(1.0f), bottom_left + bsize / 2.0f));

        }

    private:
        std::shared_ptr<Font> font;
        glm::vec4             text_color;

        std::shared_ptr<Rectangle>         background;
        std::vector<std::shared_ptr<Text>> labels;
        std::vector<std::shared_ptr<Text>> values;
    };

    StatsSystem::StatsSystem(pkzo::Engine& e) noexcept
    : System(e)
    {
        last_tick = std::chrono::steady_clock::now();
    }

    StatsSystem::~StatsSystem() = default;

    void StatsSystem::define(StatType type, const std::string& name, float initial) noexcept
    {
        // TODO thread safty
        assert(stats.find(name) == end(stats));
        stats[name] = {type, initial};
    }

    void StatsSystem::increment(const std::string& name, float value) noexcept
    {
        // TODO thread safty
        auto i = stats.find(name);
        if (i != end(stats))
        {
            assert(i->second.type == StatType::TIME || i->second.type == StatType::FRAME);
            i->second.acc += value;
        }
    }

    void StatsSystem::set(const std::string& name, float value) noexcept
    {
        // TODO thread safty
        auto i = stats.find(name);
        if (i != end(stats))
        {
            assert(i->second.type == StatType::VALUE);
            i->second.value = value;
        }
    }

    float StatsSystem::get(const std::string& name) noexcept
    {
        // TODO thread safty
        auto i = stats.find(name);
        if (i != end(stats))
        {
            return i->second.value;
        }
        else
        {
            return NAN;
        }
    }

    void StatsSystem::show()
    {
        if (!visible)
        {
            assert(screen == nullptr);
            c9y::sync([this] () {
                auto gs = engine.get_system<GraphicSystem>();
                if (!gs)
                {
                    trace("Can't show stats, no graphic system loaded.");
                    return;
                }

                const auto size = gs->get_window_size();

                auto font_file        = engine.get_setting("StatsSystem", "font",             "fonts/DejaVuSansMono.ttf");
                auto font_size        = engine.get_setting("StatsSystem", "font_size",        18u);
                auto text_color       = engine.get_setting("StatsSystem", "text_color",       rgba(0xc2d9ffff));
                auto background_color = engine.get_setting("StatsSystem", "background_color", rgba(0x101112c4));

                auto font = engine.load_asset<pkzo::Font>(font_file, font_size);

                screen = std::make_unique<StatsScreen>(size, font, text_color, background_color);
                screen->set_stats(stats);
                screen->set_engine(&engine);

                render_event = gs->debug_draw([this] () {
                    screen->draw();
                });

                visible = true;
            });
        }
    }

    void StatsSystem::hide()
    {
        if (visible)
        {
            c9y::sync([this] () {
                auto gs = engine.get_system<GraphicSystem>();
                assert(gs);
                gs->get_debug_draw_signal().disconnect(render_event);

                screen->set_engine(nullptr);
                screen = nullptr;
                visible = false;
            });
        }
    }

    bool StatsSystem::is_visible() const noexcept
    {
        return visible;
    }

    void StatsSystem::activate()
    {

    }

    void StatsSystem::tick()
    {
        auto now = std::chrono::steady_clock::now();
        auto dt  = fsec(now - last_tick).count();
        last_tick = now;

        time_accum += dt;
        bool time_rollover = (time_accum >= time_basis);
        soft_assert(time_accum < (time_basis * 2.0f));

        for (auto& [name, stat] : stats)
        {
            switch (stat.type)
            {
                case StatType::FRAME:
                    stat.value = stat.acc;
                    stat.acc = 0.0f;
                    break;
                case StatType::TIME:
                    if (time_rollover)
                    {
                        stat.value = stat.acc * time_basis / time_accum;
                        stat.acc = 0.0f;
                    }
                    break;
                case StatType::VALUE:
                default:
                    // nothing
                    break;
            }
        }

        if (time_rollover)
        {
            time_accum = 0.0f;
            // the time rollover also acts as update frequency
            if (screen)
            {
                screen->set_stats(stats);
            }
        }
    }

    void StatsSystem::deactivate()
    {
        hide();
        c9y::sync_point();
    }
}


