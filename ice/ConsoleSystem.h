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

#include <string>
#include <vector>
#include <functional>
#include <map>
#include <deque>

#include <rsig/rsig.h>

#include "System.h"
#include "Keyboard.h"

namespace ice
{
    class ConsoleSystem;
    using CommandFunc = std::function<void (const std::vector<std::string>&)>;

    class ICE_EXPORT ConsoleSystem : public ice::System
    {
    public:
        ConsoleSystem(ice::Engine& e) noexcept;

        ~ConsoleSystem();

        void define(const std::string& name, const CommandFunc& func) noexcept;

        void exec(const std::string& code);

        void write(const std::string& line) noexcept;

        void show();

        void hide();

        bool is_visible() const noexcept;

    private:
        class ConsoleScreen;

        unsigned int            max_output_lines = 5;
        ice::Key                console_key = Key::F1;

        std::map<std::string, CommandFunc> commands;
        std::deque<std::string>            output_buffer;
        std::string                        input_buffer;

        std::atomic<bool>                  visible = false;
        rsig::connection                   render_event;
        rsig::connection                   text_event;
        rsig::connection                   key_event;
        std::unique_ptr<ConsoleScreen>     screen;

    };
}


