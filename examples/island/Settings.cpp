// Garden
// Copyright 2026 Sean Farrell
// All rights reserved.

#include "Settings.h"

#include "tinyformat.h"

#include <fstream>

namespace island
{
    Settings::Settings() = default;

    Settings::Settings(const std::filesystem::path& file)
    {
        load(file);
    }

    Settings::Settings(const Settings& rhs) = default;

    Settings::Settings(Settings&& rhs) = default;

    Settings::~Settings() = default;

    Settings& Settings::operator = (const Settings& rhs) = default;

    Settings& Settings::operator = (Settings&& rhs) = default;

    void Settings::load(const std::filesystem::path& file)
    {
        auto input = std::ifstream(file);
        if (!input)
        {
            throw std::runtime_error(tfm::format("Failed to open %s for reading.", file));
        }

        settings = fkyaml::node::deserialize(input);
    }

    void Settings::save(const std::filesystem::path& file)
    {
        auto output = std::ofstream(file);
        if (!output)
        {
            throw std::runtime_error(tfm::format("Failed to open %s for writing.", file));
        }

        output << settings;
    }
}