//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef _MV_SETTINGS_H_
#define _MV_SETTINGS_H_

#include <string>
#include <map>
#include <filesystem>

namespace mv
{
    class Settings
    {
    public:
        Settings();
        Settings(const Settings&) = delete;
        ~Settings();
        Settings& operator = (const Settings&) = delete;

        bool has_value(const std::string& section, const std::string& key) const noexcept;
        template <typename Type>
        Type get_value(const std::string& section, const std::string& key, const Type& initial) noexcept;
        template <typename Type>
        void set_value(const std::string& section, const std::string& key, const Type& value) noexcept;

        void load(const std::filesystem::path& config_file);
        void save(const std::filesystem::path& config_file);

    private:
        std::map<std::string, std::map<std::string, std::string>> values;
    };

    template <typename Type>
    Type Settings::get_value(const std::string& section, const std::string& key, const Type& initial) noexcept
    {
        auto i = values.find(section);
        if (i != end(values))
        {
            auto j = i->second.find(key);
            if (j != end(i->second))
            {
                return pkzo::from_string<Type>(j->second);
            }
        }
        // apply the initial value
        values[section][key] = pkzo::to_string(initial);
        return initial;
    }

    template <typename Type>
    void Settings::set_value(const std::string& section, const std::string& key, const Type& value) noexcept
    {
        values[section][key] = pkzo::to_string(value);
    }
}
#endif
