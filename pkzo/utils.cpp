// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include "utils.h"

#include <stdexcept>
#include <algorithm>
#include <format>
#include <fstream>

#include "strconv.h"

namespace pkzo
{
    std::string tolower(const std::string& str, const std::locale& loc)
    {
        std::string result(str.size(), '\0');

        std::transform(str.begin(), str.end(), result.begin(), [&] (char c) {
            return std::tolower(c, loc);
        });

        return result;
    }

    std::string toupper(const std::string& str, const std::locale& loc)
    {
        std::string result(str.size(), '\0');

        std::transform(str.begin(), str.end(), result.begin(), [&] (char c) {
            return std::toupper(c, loc);
        });

        return result;
    }

    std::vector<std::byte> load_binary_file(const std::filesystem::path& file)
    {
        if (!std::filesystem::exists(file))
        {
            throw std::runtime_error(std::format("File '{}' does not exist.", strconv::u8compat(file.u8string())));
        }

        auto size = std::filesystem::file_size(file);

        auto buffer = std::vector<std::byte>(size);

        auto input = std::ifstream{file, std::ios::binary};
        if (!input.is_open())
        {
            throw std::runtime_error(std::format("Failed to open '{}' for reading.", strconv::u8compat(file.u8string())));
        }

        auto count = 0u;
        while (count < size)
        {
            count += input.read(reinterpret_cast<char*>(buffer.data()) + count, size - count)
                          .gcount();

            if (input.bad())
            {
                throw std::runtime_error(std::format("Failed to read '{}'.", strconv::u8compat(file.u8string())));
            }
        }

        return buffer;
    }

    std::string load_text_file(const std::filesystem::path& file)
    {
        auto buffer = load_binary_file(file);
        return std::string(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    }
}
