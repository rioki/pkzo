// State Machine
// Copyright 2022 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"

#include <ice/StateMachine.h>

enum class State
{
    INIT,
    STATE1,
    STATE2,
    END,
    ERROR = sm::StateMachine<State>::ERROR_STATE
};

TEST(StateMachine, create)
{
    auto sm = sm::StateMachine<State>(State::INIT);

    EXPECT_EQ(State::INIT, sm.get_state());
}

TEST(StateMachine, create_default_zero)
{
    auto sm = sm::StateMachine<State>();

    EXPECT_EQ(State::INIT, sm.get_state());
}

TEST(StateMachine, change_state)
{
    auto sm = sm::StateMachine<State>(State::INIT);
    EXPECT_EQ(State::INIT, sm.get_state());

    sm.change_state(State::STATE1);
    EXPECT_EQ(State::STATE1, sm.get_state());

    sm.change_state(State::STATE2);
    EXPECT_EQ(State::STATE2, sm.get_state());

    sm.change_state(State::END);
    EXPECT_EQ(State::END, sm.get_state());
}

TEST(StateMachine, queue_state)
{
    auto sm = sm::StateMachine<State>(State::INIT);
    EXPECT_EQ(State::INIT, sm.get_state());

    sm.queue_state(State::STATE1);
    EXPECT_EQ(State::INIT, sm.get_state());
    sm.tick();
    EXPECT_EQ(State::STATE1, sm.get_state());

    sm.queue_state(State::STATE2);
    EXPECT_EQ(State::STATE1, sm.get_state());
    sm.tick();
    EXPECT_EQ(State::STATE2, sm.get_state());

    sm.queue_state(State::END);
    EXPECT_EQ(State::STATE2, sm.get_state());
    sm.tick();
    EXPECT_EQ(State::END, sm.get_state());
}

TEST(StateMachine, processing_intructions)
{
    auto sm = sm::StateMachine<State>(State::INIT);

    auto state1_tick = 0u;
    sm.on_tick(State::STATE1, [&] () {
        state1_tick++;
    });

    auto state2_tick = 0u;
    sm.on_tick(State::STATE2, [&] () {
        state2_tick++;
    });

    sm.tick();

    sm.change_state(State::STATE1);
    sm.tick();
    sm.tick();

    sm.change_state(State::STATE2);
    sm.tick();
    sm.tick();
    sm.tick();

    sm.change_state(State::END);
    sm.tick();

    EXPECT_EQ(State::END, sm.get_state());
    EXPECT_EQ(2, state1_tick);
    EXPECT_EQ(3, state2_tick);
}

TEST(StateMachine, processing_intructions_with_queue_state)
{
    auto sm = sm::StateMachine<State>(State::INIT);

    auto state1_tick = 0u;
    sm.on_tick(State::STATE1, [&] () {
        state1_tick++;
    });

    auto state2_tick = 0u;
    sm.on_tick(State::STATE2, [&] () {
        state2_tick++;
    });

    sm.tick();

    sm.queue_state(State::STATE1);
    sm.tick();
    sm.tick();

    sm.queue_state(State::STATE2);
    sm.tick();
    sm.tick();
    sm.tick();

    sm.queue_state(State::END);
    sm.tick();

    EXPECT_EQ(State::END, sm.get_state());
    EXPECT_EQ(2, state1_tick);
    EXPECT_EQ(3, state2_tick);
}

TEST(StateMachine, pre_and_post_intructions)
{
    auto sm = sm::StateMachine<State>(State::INIT);

    auto state1_enter = 0u;
    sm.on_enter(State::STATE1, [&] () {
        state1_enter++;
    });
    auto state1_exit = 0u;
    sm.on_exit(State::STATE1, [&] () {
        state1_exit++;
    });

    auto state2_enter = 0u;
    sm.on_enter(State::STATE2, [&] () {
        state2_enter++;
    });
    auto state2_exit = 0u;
    sm.on_exit(State::STATE2, [&] () {
        state2_exit++;
    });

    sm.tick();

    sm.change_state(State::STATE1);
    sm.tick();
    sm.tick();

    sm.change_state(State::STATE2);
    sm.tick();
    sm.tick();
    sm.tick();

    sm.change_state(State::END);
    sm.tick();

    EXPECT_EQ(State::END, sm.get_state());
    EXPECT_EQ(1, state1_enter);
    EXPECT_EQ(1, state1_exit);
    EXPECT_EQ(1, state1_enter);
    EXPECT_EQ(1, state1_exit);
}

TEST(StateMachine, pre_and_post_intructions_queue_state)
{
    auto sm = sm::StateMachine<State>(State::INIT);

    auto state1_enter = 0u;
    sm.on_enter(State::STATE1, [&] () {
        state1_enter++;
    });
    auto state1_exit = 0u;
    sm.on_exit(State::STATE1, [&] () {
        state1_exit++;
    });

    auto state2_enter = 0u;
    sm.on_enter(State::STATE2, [&] () {
        state2_enter++;
    });
    auto state2_exit = 0u;
    sm.on_exit(State::STATE2, [&] () {
        state2_exit++;
    });

    sm.tick();

    sm.queue_state(State::STATE1);
    sm.tick();
    sm.tick();

    sm.queue_state(State::STATE2);
    sm.tick();
    sm.tick();
    sm.tick();

    sm.queue_state(State::END);
    sm.tick();

    EXPECT_EQ(State::END, sm.get_state());
    EXPECT_EQ(1, state1_enter);
    EXPECT_EQ(1, state1_exit);
    EXPECT_EQ(1, state1_enter);
    EXPECT_EQ(1, state1_exit);
}

TEST(StateMachine, exception_handling_in_tick)
{
    auto sm = sm::StateMachine<State>(State::INIT);

    sm.on_tick(State::STATE1, [&] () {
        throw std::runtime_error("error in state 1");
    });

    sm.on_tick(State::STATE2, [&] () {
        throw std::runtime_error("error in state 2");
    });

    sm.tick();

    sm.change_state(State::STATE1);
    EXPECT_THROW(sm.tick(), std::runtime_error);
    EXPECT_EQ(State::STATE1, sm.get_state());

    sm.change_state(State::STATE2);
    EXPECT_THROW(sm.tick(), std::runtime_error);
    EXPECT_EQ(State::STATE2, sm.get_state());

    sm.change_state(State::END);
    sm.tick();
}

TEST(StateMachine, exception_handling_in_enter)
{
    auto sm = sm::StateMachine<State>(State::INIT);

    sm.on_enter(State::STATE2, [&] () {
        throw std::runtime_error("error enter state 2");
    });

    sm.change_state(State::STATE1);
    EXPECT_THROW(sm.change_state(State::STATE2), std::runtime_error);
    EXPECT_EQ(State::ERROR, sm.get_state());
    EXPECT_TRUE(sm.is_invalid());
}


TEST(StateMachine, exception_handling_in_exit)
{
    auto sm = sm::StateMachine<State>(State::INIT);

    sm.on_exit(State::STATE1, [&] () {
        throw std::runtime_error("error exit state 2");
    });

    sm.change_state(State::STATE1);
    EXPECT_THROW(sm.change_state(State::STATE2), std::runtime_error);
    EXPECT_EQ(State::ERROR, sm.get_state());
    EXPECT_TRUE(sm.is_invalid());
}
