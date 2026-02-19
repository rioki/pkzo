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

#pragma once

#include <chrono>
#include <source_location>
#include <deque>

#include <pkzo2d/pkzo2d.h>

namespace lab
{
    class Pawn;

    class DebugOverlay : public pkzo2d::Screen
    {
    public:
        DebugOverlay(const glm::vec2& size);

        void update(float dt) override;

    private:
        using time_point = std::chrono::steady_clock::time_point;

        pkzo2d::Text* fps_counter;
        time_point    last_fps_count;
        size_t        frame_count = 0;

        struct LogLine
        {
            time_point    time;
            pkzo2d::Text* widget = nullptr;
        };
        std::deque<LogLine> log_lines;
        rsig::connection trace_connection;
        std::shared_ptr<pkzo::Font> text_font;

        void update_fps();

        void handle_trace(const std::source_location& loc, const std::string_view msg);
        void prune_log_lines(bool inserting = false);
    };
}
