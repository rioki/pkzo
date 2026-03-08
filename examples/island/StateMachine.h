// State Machine
// Copyright 2022-2026 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <optional>
#include <functional>
#include <map>
#include <variant>

namespace rex
{
    //! State Machine
    //!
    //! StateMachine implements a simple enter/tick/exit state machine driven
    //! by a user-defined enum. The enum must define at least two reserved
    //! values: INIT, which is the default initial state, and ERROR, which
    //! the machine enters automatically if an enter or exit callback throws.
    //!
    //! An optional second template parameter EventVariant enables event
    //! routing. When provided, events are dispatched to the handler registered
    //! for the current state via send_event(). States with no event handler
    //! silently ignore events. If omitted, the event API is unavailable.
    //!
    //! State transitions are deferred; queue_state() schedules a transition
    //! that is applied at the start of the next tick(), before the tick
    //! callback runs.
    //!
    //! Callbacks are optional for every state. If no callback is registered
    //! for a given state and event, the event is silently ignored.
    template <typename StateEnum, typename EventVariant = std::monostate>
    class StateMachine
    {
    public:
        //! Construct state machine with state INIT
        StateMachine() noexcept = default;

        //! Construct a state machine with a custom initial state.
        //!
        //! Use this constructor when you want to bypass INIT and start
        //! directly in a specific state, without triggering its enter callback.
        //!
        //! @param initial_state the initial state
        StateMachine(StateEnum initial_state) noexcept
        : state(initial_state) {}

        //! Get the current state.
        [[nodiscard]]
        StateEnum get_state() const noexcept
        {
            return state;
        }

        //! Schedule a state transition to occur at the start of the next tick.
        //!
        //! The transition is not applied immediately; it will be processed at
        //! the beginning of the next call to tick(), before the tick callback
        //! runs. Calling this multiple times before the next tick will replace
        //! the previously queued state.
        //!
        //! This is the preferred way to trigger transitions from within a tick
        //! callback, as it avoids re-entrant state changes.
        //!
        //! @param new_state The state to transition to on the next tick.
        void queue_state(StateEnum new_state) noexcept
        {
            next_state = new_state;
        }

        //! Advance the state machine by one time step.
        //!
        //! If a state transition was queued via queue_state(), it is applied
        //! first, including its enter and exit callbacks. The tick callback of
        //! the resulting state is then called with the given delta time.
        //!
        //! @param dt  Delta time in seconds since the last tick.
        //! @throws std::runtime_error if the machine is in the ERROR state.
        //! @throws Any exception thrown by a queued state transition's callbacks.
        void tick(float dt)
        {
            if (state == StateEnum::ERROR)
            {
                throw std::runtime_error("The state machine is in error state.");
            }

            if (next_state)
            {
                change_state(*next_state);
                next_state = std::nullopt;
            }

            auto i = tick_functions.find(state);
            if (i != end(tick_functions))
            {
                auto& func = i->second;
                func(dt);
            }
        }

        //! Dispatch an event to the handler registered for the current state.
        //!
        //! The event is delivered immediately and synchronously to the handler
        //! of the current state, if one is registered. States with no event
        //! handler silently ignore the event.
        //!
        //! This overload is only available when EventVariant is not std::monostate,
        //! i.e. when the state machine was instantiated with an event type.
        //!
        //! @param event  The event to dispatch.
        template <typename E = EventVariant>
        std::enable_if_t<!std::is_same_v<E, std::monostate>> send_event(const EventVariant& event)
        {
            auto i = event_functions.find(state);
            if (i != end(event_functions))
            {
                i->second(event);
            }
        }

        //! Register a callback to be invoked when entering a state.
        //!
        //! @param state  The state to register the callback for.
        //! @param func   Callback invoked when the machine enters this state.
        //! @throws std::invalid_argument if func is null.
        //! @throws std::logic_error if a callback is already registered for this state.
        void on_enter(StateEnum state, const std::function<void ()>& func)
        {
            if (func == nullptr)
            {
                throw std::invalid_argument("StateMachine::on_enter: func is null");
            }
            if (enter_functions.find(state) != end(enter_functions))
            {
                throw std::logic_error("StateMachine::on_enter: state is already registered.");
            }
            enter_functions[state] = func;
        }

        //! Register a callback to be invoked each tick while in a state.
        //!
        //! @param state  The state to register the callback for.
        //! @param func   Callback invoked each tick, receiving the delta time in seconds.
        //! @throws std::invalid_argument if func is null.
        //! @throws std::logic_error if a callback is already registered for this state.
        void on_tick(StateEnum state, const std::function<void (float)>& func)
        {
            if (func == nullptr)
            {
                throw std::invalid_argument("StateMachine::on_tick: func is null");
            }
            if (tick_functions.find(state) != end(tick_functions))
            {
                throw std::logic_error("StateMachine::on_tick: state is already registered.");
            }
            tick_functions[state] = func;
        }

        //! Register a callback to be invoked when exiting a state.
        //!
        //! @param state  The state to register the callback for.
        //! @param func   Callback invoked when the machine leaves this state.
        //! @throws std::invalid_argument if func is null.
        //! @throws std::logic_error if a callback is already registered for this state.
        void on_exit(StateEnum state, const std::function<void ()>& func)
        {
            if (func == nullptr)
            {
                throw std::invalid_argument("StateMachine::on_exit: func is null");
            }
            if (exit_functions.find(state) != end(exit_functions))
            {
                throw std::logic_error("StateMachine::on_exit: state is already registered.");
            }
            exit_functions[state] = func;
        }

        //! Register a callback to be invoked when an event is dispatched in a state.
        //!
        //! Only available when the state machine was instantiated with an event type.
        //! The callback receives the event by const reference and should use
        //! std::visit to handle the specific event types within the variant.
        //!
        //! @param state  The state to register the callback for.
        //! @param func   Callback invoked when an event is dispatched in this state.
        //! @throws std::invalid_argument if func is null.
        //! @throws std::logic_error if a callback is already registered for this state.
        template <typename E = EventVariant>
        std::enable_if_t<!std::is_same_v<E, std::monostate>>
        on_event(StateEnum state, const std::function<void (const EventVariant&)>& func)
        {
            if (func == nullptr)
            {
                throw std::invalid_argument("StateMachine::on_event: func is null");
            }
            if (event_functions.find(state) != end(event_functions))
            {
                throw std::logic_error("StateMachine::on_event: state is already registered.");
            }
            event_functions[state] = func;
        }

    private:
        StateEnum                state      = StateEnum::INIT;
        std::optional<StateEnum> next_state = std::nullopt;

        std::map<StateEnum, std::function<void (float)>>                tick_functions;
        std::map<StateEnum, std::function<void ()>>                     enter_functions;
        std::map<StateEnum, std::function<void ()>>                     exit_functions;
        std::map<StateEnum, std::function<void (const EventVariant&)>>  event_functions;

        void change_state(StateEnum new_state)
        {
            // exceptions in enter or exit are unrecoverable
            try
            {
                auto i = exit_functions.find(state);
                if (i != end(exit_functions))
                {
                    auto& func = i->second;
                    func();
                }

                state = new_state;

                auto j = enter_functions.find(state);
                if (j != end(enter_functions))
                {
                    auto& func = j->second;
                    func();
                }
            }
            catch (...)
            {
                state = StateEnum::ERROR;
                next_state = std::nullopt;
                throw;
            }
        }

        StateMachine(const StateMachine&) = delete;
        StateMachine& operator = (const StateMachine&) = delete;
    };
}
