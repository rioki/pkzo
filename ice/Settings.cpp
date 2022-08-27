// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "Settings.h"

namespace ice
{
    Settings::Settings() noexcept = default;
    Settings::~Settings() = default;

     std::string Settings::get_value(const std::string& section, const std::string& key, const std::string& initial) const noexcept
     {
        return get_value<std::string>(section, key, initial);
     }

    void Settings::load(const std::filesystem::path& file)
    {
        auto input = std::ifstream(file);
        if (!input.is_open())
        {
            throw std::runtime_error(std::format("Failed to open '{}' for reading.", file.string()));
        }

        jvalues = nlohmann::json::parse(input);
    }

    void Settings::save(const std::filesystem::path& file)
    {
        auto output = std::ofstream{file};
        output << jvalues;
    }
}
