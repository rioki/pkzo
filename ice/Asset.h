// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <atomic>
#include <filesystem>

namespace ice
{
    class ICE_EXPORT Asset
    {
    public:
        Asset() noexcept;
        virtual ~Asset();

        unsigned int get_id() const noexcept;

    private:
        static std::atomic<unsigned int> last_id;

        const unsigned int id;

        Asset(const Asset&) = delete;
        Asset& operator = (const Asset&) = delete;
    };
}


