// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "DebugOverlay.h"

#include <pkzo/debug.h>
#include <pkzo/color.h>
#include <pkzo/strconv.h>

#include "env.h"

using namespace std::chrono_literals;

namespace lab
{
    using fsec = std::chrono::duration<float>;
    using namespace pkzo;

    constexpr auto PRIMARY_COLOR    = glm::vec4(1.0f);
    constexpr auto FONT             = "fonts/DejaVuSansMono.ttf";
    constexpr auto TEXT_FONT_SIZE   = 12u;

    constexpr auto FPS_INTERVALL    = 1s;
    constexpr auto LOG_OFFSET       = 30.0f;
    constexpr auto LOG_MAX_LINES    = 5u;
    constexpr auto LOG_LIFE         = 5s;
    constexpr auto LOG_FADE         = 1s;

    DebugOverlay::DebugOverlay(const glm::vec2& size)
    : Screen({size})
    {
        trace_connection = pkzo::on_trace([this] (const std::source_location& loc, const std::string_view msg) { handle_trace(loc, msg); });

        auto half_size = size / 2.0f;

        auto base = get_asset_folder();
        text_font  = pkzo::Font::load(base / FONT),

        fps_counter = add<Text>({
            .transform = position(half_size.x - 70.0f, half_size.y - 30.0f),
            .text      = u8"00.00 fps",
            .color     = PRIMARY_COLOR,
            .font      = text_font,
            .font_size = TEXT_FONT_SIZE
        });
        last_fps_count = std::chrono::steady_clock::now();
    }

    void DebugOverlay::update(float dt)
    {
        update_fps();
        prune_log_lines();

        Screen::update(dt);
    }

    void DebugOverlay::update_fps()
    {
        frame_count++;

        auto now = std::chrono::steady_clock::now();
        if (now - last_fps_count > FPS_INTERVALL)
        {
            auto dt = std::chrono::duration_cast<fsec>(now - last_fps_count).count();
            auto fps = static_cast<float>(frame_count) / dt;

            fps_counter->set_text(strconv::utf8(tfm::format("%.2f fps", fps)));

            last_fps_count = now;
            frame_count    = 0;
        }
    }

    void DebugOverlay::prune_log_lines(bool inserting)
    {
        auto changed = inserting;

        while (log_lines.size() > LOG_MAX_LINES)
        {
            changed = true;
            remove(log_lines.back().widget);
            log_lines.pop_back();
        }

        auto now = std::chrono::steady_clock::now();
        std::erase_if(log_lines, [&] (auto const& e) mutable
        {
            if (now - e.time > LOG_LIFE)
            {
                remove(e.widget);
                changed = true;
                return true;
            }
            return false;
        });

        for (auto i = begin(log_lines); i != end(log_lines); ++i)
        {
            if (now - i->time > (LOG_LIFE - LOG_FADE))
            {
                auto life_time  = now - i->time;
                auto fade_start = LOG_LIFE - LOG_FADE;
                auto remaining  = life_time - fade_start;

                float t = std::chrono::duration_cast<fsec>(remaining).count() / std::chrono::duration_cast<fsec>(LOG_FADE).count();
                t = std::clamp(t, 0.0f, 1.0f);

                auto color = i->widget->get_color();
                color.a = 1.0f - t;
                i->widget->set_color(color);
                // no change in position so don't touch changed
            }
        }

        if (changed)
        {
            auto size      = get_size();
            auto half_size = size / 2.0f;

            auto pos = glm::vec2(-half_size.x + 30.0f, half_size.y - 30.0f);

            for (auto i = begin(log_lines); i != end(log_lines); ++i)
            {
                auto widget_size = i->widget->get_size();
                auto whs = widget_size / 2.0f;
                i->widget->set_transform(position(pos.x + whs.x, pos.y + whs.y));

                pos.y -= LOG_OFFSET;
            }
        }
    }

    void DebugOverlay::handle_trace(const std::source_location& loc, const std::string_view msg)
    {
        auto text = strconv::utf8(tfm::format("%s(%d): %s", pkzo::basename(loc.file_name()), loc.line(), msg));
        auto line_size = glm::vec2(text_font->estimate(text, TEXT_FONT_SIZE));
        auto whs = line_size / 2.0f;

        auto size      = get_size();
        auto half_size = size / 2.0f;

        auto pos = glm::vec2(-half_size.x + 30.0f, half_size.y - 30.0f - log_lines.size() * LOG_OFFSET);

        auto line = add<Text>({
            .text      = text,
            .color     = PRIMARY_COLOR,
            .font      = text_font,
            .font_size = TEXT_FONT_SIZE
        });

        log_lines.push_front({std::chrono::steady_clock::now(), line});

        prune_log_lines(true);
    }
}
