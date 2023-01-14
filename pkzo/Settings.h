// pkzo
// Copyright 2022-2023 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "config.h"

#include <string>
#include <filesystem>

#include <nlohmann/json.hpp>
#include "glm_json.h"

namespace pkzo
{
    class ICE_EXPORT Settings
    {
    public:
        Settings() noexcept;
        ~Settings();

        template <typename Type> [[nodiscard]]
        Type get_value(const std::string& section, const std::string& key, const Type& initial) const noexcept;
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
