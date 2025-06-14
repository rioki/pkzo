// pkzo
// Copyright 2025 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include <filesystem>
#include <string_view>

#include "fkyaml.hpp"

namespace pkzo
{
    //! Settings
    class PKZO_API Settings
    {
    public:
        Settings() = default;
        ~Settings() = default;

        //! Load Settings
        void load(const std::filesystem::path& file);

        //! Save Settings
        void save(const std::filesystem::path& file);

        //! Get a settings entry.
        template <typename Type>
        Type get(const std::string_view section, const std::string_view& key, const Type& fallback);

        //! Set a settings entry.
        template <typename Type>
        void set(const std::string_view section, const std::string_view& key, const Type& value);

    private:
        fkyaml::node data = fkyaml::node::mapping();

        Settings(const Settings&) = delete;
        Settings& operator = (const Settings&) = delete;
    };

    template <typename Type>
    Type Settings::get(const std::string_view section, const std::string_view& key, const Type& fallback)
    {
        if (!data.contains(section))
        {
            return fallback;
        }

        auto yaml_section = data[section];
        if (!yaml_section.contains(key))
        {
            return fallback;
        }

        return yaml_section[key].get_value<Type>();
    }

    template <typename Type>
    void Settings::set(const std::string_view section, const std::string_view& key, const Type& value)
    {
        if (!data.contains(section))
        {
            data[section] = fkyaml::node::mapping();
        }
        data[section][key] = value;
    }
}