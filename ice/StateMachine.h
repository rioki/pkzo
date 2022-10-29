// State Machine
// Copyright 2022 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <cassert>
#include <optional>
#include <functional>
#include <map>

namespace sm
{
    template <typename StateEnum>
    class StateMachine
    {
    public:
        StateMachine() noexcept = default;

        StateMachine(StateEnum initial_state) noexcept
        : state(initial_state) {}

        StateEnum get_state() const noexcept
        {
            return state;
        }

        void change_state(StateEnum new_state) noexcept
        {
            auto i = exit_functions.find(state);
            if (i != end(exit_functions))
            {
                auto& func = i->second;
                assert(func);
                func();
            }

            state = new_state;

            auto j = enter_functions.find(state);
            if (j != end(enter_functions))
            {
                auto& func = j->second;
                assert(func);
                func();
            }
        }

        void queue_state(StateEnum new_state) noexcept
        {
            next_state = new_state;
        }

        void tick() noexcept
        {
            if (next_state)
            {
                change_state(*next_state);
                next_state = std::nullopt;
            }

            auto i = tick_functions.find(state);
            if (i != end(tick_functions))
            {
                auto& func = i->second;
                assert(func);
                func();
            }
        }

        void on_enter(StateEnum state, const std::function<void ()>& func)
        {
            assert(func);
            assert(enter_functions.find(state) == end(enter_functions));
            enter_functions[state] = func;
        }

        void on_tick(StateEnum state, const std::function<void ()>& func)
        {
            assert(func);
            assert(tick_functions.find(state) == end(tick_functions));
            tick_functions[state] = func;
        }

        void on_exit(StateEnum state, const std::function<void ()>& func)
        {
            assert(func);
            assert(exit_functions.find(state) == end(exit_functions));
            exit_functions[state] = func;
        }

    private:
        StateEnum                state      = static_cast<StateEnum>(0);
        std::optional<StateEnum> next_state = std::nullopt;

        std::map<StateEnum, std::function<void ()>> tick_functions;
        std::map<StateEnum, std::function<void ()>> enter_functions;
        std::map<StateEnum, std::function<void ()>> exit_functions;

        StateMachine(const StateMachine&) = delete;
        StateMachine& operator = (const StateMachine&) = delete;
    };
}
