// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

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


