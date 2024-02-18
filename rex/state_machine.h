// Neon Skirmish
// Copyright 2023 Sean Farrell
// All rights reserved.

#pragma once

#include <functional>
#include <map>
#include <limits>
#include <type_traits>

namespace rex
{
    template <typename E>
    class state_machine
    {
    public:
        using underlying_t = std::underlying_type_t<E>;
        static constexpr underlying_t ERROR = static_cast<underlying_t>(std::numeric_limits<underlying_t>::max());

        state_machine() noexcept = default;
        ~state_machine() noexcept = default;

        void on_enter(E state, const std::function<void ()>& cb) noexcept
        {
            state_handlers[state].enter = cb;
        }

        void on_process(E state, const std::function<void ()>& cb) noexcept
        {
            state_handlers[state].process = cb;
        }

        void on_exit(E state, const std::function<void ()>& cb) noexcept
        {
            state_handlers[state].exit = cb;
        }

        E get_state() const noexcept
        {
            return current_state;
        }

        void queue_state(E value) noexcept
        {
            next_state = value;
        }

        void process()
        {
            if (next_state == static_cast<E>(ERROR))
            {
                throw std::runtime_error("The state machine is in error state.");
            }

            // exceptions in enter or exit are unrecoverable
            try
            {
                if (next_state != current_state)
                {
                    if (state_handlers[current_state].exit)
                    {
                        state_handlers[current_state].exit();
                    }
                    current_state = next_state;
                    if (state_handlers[current_state].enter)
                    {
                        state_handlers[current_state].enter();
                    }
                }
            }
            catch (...)
            {
                next_state    = static_cast<E>(ERROR);
                current_state = static_cast<E>(ERROR);
                throw;
            }

            if (state_handlers[current_state].process)
            {
                state_handlers[current_state].process();
            }
        }

    private:
        E current_state = {};
        E next_state    = {};

        struct state_handlers
        {
            std::function<void ()> enter;
            std::function<void ()> process;
            std::function<void ()> exit;
        };
        std::map<E, state_handlers> state_handlers;

        state_machine(const state_machine&) = delete;
        state_machine& operator = (const state_machine&) = delete;
    };
}

