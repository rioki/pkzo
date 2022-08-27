// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once

#include "config.h"

#include <string>
#include <optional>
#include <filesystem>

#include <nlohmann/json.hpp>

namespace ice
{
    class ICE_EXPORT Settings
    {
    public:
        Settings() noexcept;
        ~Settings();

        template <typename Type> [[nodiscard]]
        Type get_value(const std::string& section, const std::string& key, const Type& initial) const noexcept;

        [[nodiscard]]
        std::string get_value(const std::string& section, const std::string& key, const std::string& initial) const noexcept;

        template <typename Type> [[nodiscard]]
        void set_value(const std::string& section, const std::string& key, const Type& value) noexcept;

        void load(const std::filesystem::path& file);
        void save(const std::filesystem::path& file);

    private:
        nlohmann::json jvalues;

        Settings(const Settings&) = delete;
        Settings& operator = (const Settings&) = delete;
    };

    template <typename Type>
    Type Settings::get_value(const std::string& section, const std::string& key, const Type& initial) const noexcept
    {
        auto si = jvalues.find(section);
        if (si == end(jvalues))
        {
            return initial;
        }

        const auto& sec = *si;
        auto ki = sec.find(key);
        if (ki == end(sec))
        {
            return initial;
        }

        return ki->get<Type>();
    }

    template <typename Type>
    void Settings::set_value(const std::string& section, const std::string& key, const Type& value) noexcept
    {
        jvalues[section][key] = value;
    }
}
