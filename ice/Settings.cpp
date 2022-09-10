// Ice Engine
// Copyright 2022 Sean Farrell
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
