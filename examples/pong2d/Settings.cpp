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

#include "pch.h"
#include "Settings.h"

namespace pong2d
{
    Settings::Settings() = default;
    Settings::~Settings() = default;

    bool Settings::has_value(const std::string& section, const std::string& key) const noexcept
    {
        auto i = values.find(section);
        if (i != cend(values))
        {
            auto j = i->second.find(key);
            if (j != cend(i->second))
            {
                return true;
            }
        }
        return false;
    }

    void Settings::load(const std::filesystem::path& config_file)
    {
        using nlohmann::json;

        auto input = std::ifstream(config_file);
        if (!input.is_open())
        {
            throw std::runtime_error("Failed to open seetings for reading.");
        }

        std::map<std::string, std::map<std::string, std::string>> tmp;
        auto jconfig = json::parse(input);
        values = jconfig.get<std::map<std::string, std::map<std::string, std::string>>>();
    }

    void Settings::save(const std::filesystem::path& config_file)
    {
        using nlohmann::json;

        std::ofstream output(config_file);
        if (!output.is_open())
        {
            throw std::runtime_error("Failed to open settings for writing.");
        }
        output << std::setw(2) << json(values) << std::endl;

    }

}
