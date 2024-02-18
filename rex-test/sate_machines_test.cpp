// Neon Skirmish
// Copyright 2023 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <rex/state_machine.h>

enum class State
{
    INITIAL,
    FIRST,
    SECOND,
    FINAL,
    ERROR = rex::state_machine<State>::ERROR
};

TEST(state_machine, default_is_initial)
{
    auto sm = rex::state_machine<State>{};
    EXPECT_EQ(State::INITIAL, sm.get_state());
}

TEST(state_machine, change_state)
{
    auto sm = rex::state_machine<State>{};
    sm.queue_state(State::FIRST);
    EXPECT_EQ(State::INITIAL, sm.get_state());

    sm.process();
    EXPECT_EQ(State::FIRST, sm.get_state());
}

TEST(state_machine, processing)
{
    auto sm = rex::state_machine<State>{};

    auto first_processing = 0u;
    sm.on_process(State::FIRST, [&] () { first_processing++; });
    auto second_processing = 0u;
    sm.on_process(State::SECOND, [&] () { second_processing++; });

    sm.process();
    EXPECT_EQ(0u, first_processing);
    EXPECT_EQ(0u, second_processing);

    sm.queue_state(State::FIRST);
    sm.process();
    EXPECT_EQ(1u, first_processing);
    EXPECT_EQ(0u, second_processing);

    sm.process();
    EXPECT_EQ(2u, first_processing);
    EXPECT_EQ(0u, second_processing);

    sm.queue_state(State::SECOND);
    sm.process();
    EXPECT_EQ(2u, first_processing);
    EXPECT_EQ(1u, second_processing);

    sm.process();
    EXPECT_EQ(2u, first_processing);
    EXPECT_EQ(2u, second_processing);

    sm.queue_state(State::FINAL);
    sm.process();
    EXPECT_EQ(2u, first_processing);
    EXPECT_EQ(2u, second_processing);
}

TEST(state_machine, enter_and_exit)
{
    auto sm = rex::state_machine<State>{};

    auto first_enter = 0u;
    sm.on_enter(State::FIRST, [&] () { first_enter++; });
    auto second_enter = 0u;
    sm.on_enter(State::SECOND, [&] () { second_enter++; });

    auto first_exit = 0u;
    sm.on_exit(State::FIRST, [&] () { first_exit++; });
    auto second_exit = 0u;
    sm.on_exit(State::SECOND, [&] () { second_exit++; });

    sm.queue_state(State::FIRST);
    sm.process();
    EXPECT_EQ(1u, first_enter);
    EXPECT_EQ(0u, second_enter);
    EXPECT_EQ(0u, first_exit);
    EXPECT_EQ(0u, second_exit);

    sm.queue_state(State::SECOND);
    sm.process();
    EXPECT_EQ(1u, first_enter);
    EXPECT_EQ(1u, second_enter);
    EXPECT_EQ(1u, first_exit);
    EXPECT_EQ(0u, second_exit);

    sm.queue_state(State::FINAL);
    sm.process();
    EXPECT_EQ(1u, first_enter);
    EXPECT_EQ(1u, second_enter);
    EXPECT_EQ(1u, first_exit);
    EXPECT_EQ(1u, second_exit);
}

TEST(state_machine, processing_exception)
{
    auto sm = rex::state_machine<State>{};

    sm.on_process(State::FIRST, [] () { throw std::runtime_error("test"); });

    sm.queue_state(State::FIRST);
    EXPECT_THROW(sm.process(), std::runtime_error);
}

TEST(state_machine, enter_exception_is_error)
{
    auto sm = rex::state_machine<State>{};

    sm.on_enter(State::FIRST, [] () { throw std::runtime_error("test"); });

    sm.queue_state(State::FIRST);
    EXPECT_THROW(sm.process(), std::runtime_error);
    EXPECT_EQ(State::ERROR, sm.get_state());
}

TEST(state_machine, exit_exception_is_error)
{
    auto sm = rex::state_machine<State>{};

    sm.on_exit(State::FIRST, [] () { throw std::runtime_error("test"); });

    sm.queue_state(State::FIRST);
    sm.process();
    sm.queue_state(State::SECOND);
    EXPECT_THROW(sm.process(), std::runtime_error);
    EXPECT_EQ(State::ERROR, sm.get_state());
}
