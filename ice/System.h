// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

namespace ice
{
    class Engine;

    class ICE_EXPORT System
    {
    public:
        System(Engine& e) noexcept
        : engine(e) {}

        virtual ~System() = default;

        virtual void tick() = 0;

    protected:
        Engine& engine;

    private:
        System(const System&) = delete;
        System& operator = (const System&) = delete;
    };
}