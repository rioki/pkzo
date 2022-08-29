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
        Asset(const std::filesystem::path& file) noexcept;
        virtual ~Asset();

        unsigned int get_id() const noexcept;

        const std::filesystem::path& get_file() const noexcept;

    private:
        static std::atomic<unsigned int> last_id;

        const unsigned int id;
        const std::filesystem::path file;

        Asset(const Asset&) = delete;
        Asset& operator = (const Asset&) = delete;
    };
}


