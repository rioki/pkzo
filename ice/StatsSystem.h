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

#pragma once
#include "config.h"

#include <atomic>
#include <memory>
#include <string>
#include <optional>
#include <chrono>
#include <map>

#include "System.h"
#include "Keyboard.h"

namespace ice
{
    enum class StatType
    {
        VALUE,
        TIME,
        FRAME
    };

    class ICE_EXPORT StatsSystem : public ice::System
    {
    public:
        StatsSystem(ice::Engine& e) noexcept;

        ~StatsSystem();

        void define(StatType type, const std::string& name, float initial = 0.0f) noexcept;
        void increment(const std::string& name, float value = 1.0f) noexcept;
        void set(const std::string& name, float value) noexcept;
        float get(const std::string& name) noexcept;

        void show();
        void hide();
        bool is_visible() const noexcept;

        void activate() override;
        void tick() override;
        void deactivate() override;

    private:
        class StatsScreen;

        struct Stat
        {
            StatType type;
            float    value; // the last avaraged value
            float    acc;   // the current accumulation buffer
        };

        std::map<std::string, Stat>         stats;

        float                                 time_basis = 1.0f; // in seconds
        float                                 time_accum = 0;
        std::chrono::steady_clock::time_point last_tick;

        std::atomic<bool>                   visible = false;
        rsig::connection                    render_event;
        std::unique_ptr<StatsScreen>        screen;
    };
}


