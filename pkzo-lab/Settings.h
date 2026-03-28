// pkzo
// Copyright 2010-2026 Sean Farrell
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

#include <filesystem>

#include <fkYAML/node.hpp>

namespace lab
{
    //! Application Settings
    //!
    //! Settings provides a persistent key-value store organized into named
    //! sections, backed by a YAML file. Values are typed and accessed via
    //! get() and set(), with an optional fallback for missing keys.
    //!
    //! Settings can be loaded from and saved to a file at any time, or
    //! supplied at construction. The internal state is a fkyaml node tree
    //! and can round-trip through YAML without loss.
    class Settings
    {
    public:
        //! Construct an empty settings object.
        Settings();

        //! Construct a settings object and load from a file.
        //!
        //! @param file  Path to the YAML file to load.
        //! @throws std::runtime_error if the file cannot be opened.
        Settings(const std::filesystem::path& file);

        //! Copy a settings object.
        Settings(const Settings& rhs);

        //! Move a settings object.
        Settings(Settings&& rhs);

        //! Destroy the settings object.
        ~Settings();

        //! Copy-assign a settings object.
        Settings& operator = (const Settings& rhs);

        //! Move-assign a settings object.
        Settings& operator = (Settings&& rhs);

        //! Load settings from a YAML file, replacing all current state.
        //!
        //! @param file  Path to the YAML file to load.
        //! @throws std::runtime_error if the file cannot be opened.
        void load(const std::filesystem::path& file);

        //! Save current settings to a YAML file.
        //!
        //! @param file  Path to the YAML file to write.
        //! @throws std::runtime_error if the file cannot be opened
        void save(const std::filesystem::path& file);

        //! Set a value in a given section.
        //!
        //! If the section does not exist, it is created. If the key already
        //! exists, its value is overwritten.
        //!
        //! @param section  The section name.
        //! @param key      The key within the section.
        //! @param value    The value to store.
        template <typename Type>
        void set(const std::string& section, const std::string& key, const Type& value);

        //! Get a value from a given section, returning a fallback if absent.
        //!
        //! @param section   The section name.
        //! @param key       The key within the section.
        //! @param fallback  Value returned if the section or key is not found.
        //! @returns The stored value, or fallback if not found.
        template <typename Type>
        Type get(const std::string& section, const std::string& key, const Type& fallback) const;

        //! Get a value from a given section.
        //!
        //! @param section  The section name.
        //! @param key      The key within the section.
        //! @returns The stored value.
        //! @throws std::out_of_range if the section or key does not exist.
        template <typename Type>
        Type get(const std::string& section, const std::string& key) const;

    private:
        fkyaml::node settings = fkyaml::node::mapping();
    };

    template <typename Type>
    void Settings::set(const std::string& section, const std::string& key, const Type& value)
    {
        if (!settings.contains(section))
        {
            settings[section] = fkyaml::node::mapping();
        }

        settings[section][key] = value;
    }

    template <typename Type>
    Type Settings::get(const std::string& section, const std::string& key, const Type& fallback) const
    {
        if (!settings.contains(section))
        {
            return fallback;
        }

        auto& sec = settings.at(section);
        if (!sec.contains(key))
        {
            return fallback;
        }

        return sec.at(key).get_value<Type>();
    }

    template <typename Type>
    Type Settings::get(const std::string& section, const std::string& key) const
    {
        return settings.at(section).at(key).get_value<Type>();
    }
}
