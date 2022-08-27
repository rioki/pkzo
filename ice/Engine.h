// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <filesystem>

#include "Settings.h"

namespace ice
{
    class ICE_EXPORT Engine
    {
    public:
        Engine();

        ~Engine();

        [[nodiscard]]
        Settings& get_settings() noexcept;

        [[nodiscard]]
        const Settings& get_settings() const noexcept;

        void load_settings(const std::filesystem::path& file);

        void save_settings(const std::filesystem::path& file);

    private:
        Settings settings;

        Engine(const Engine&) = delete;
        Engine& operator = (const Engine&) = delete;
    };
}
