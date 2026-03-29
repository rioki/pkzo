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

#include <vector>
#include <magic_enum/magic_enum.hpp>
#include <magic_enum/magic_enum_iostream.hpp>

#include <fkYAML/node.hpp>
#include <tinyformat.h>

namespace pkzo
{
    using namespace magic_enum::iostream_operators;
    using namespace magic_enum::bitwise_operators;

    template <typename Node, typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
    void to_node(Node& node, Enum value)
    {
        node = magic_enum::enum_name(value);
    }

    template <typename Node, typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
    void from_node(const Node& node, Enum& value)
    {
        auto str = node.get_value<std::string>();
        auto v = magic_enum::enum_cast<Enum>(str, magic_enum::case_insensitive);
        if (v.has_value())
        {
            value = v.value();
        }
        else
        {
            throw std::runtime_error(tfm::format("%s is not a valid value for %s.", str, magic_enum::enum_type_name<Enum>()));
        }
    }

    //! Check if a given enum value is one of the given enums.
    //!
    //! @param value the value to check
    //! @param options the options to comare to
    //! @returns true if the value matches one of the options
    template <typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
    [[nodiscard]] constexpr
    bool one_of(Enum value, std::vector<Enum> options) noexcept
    {
        for (const auto& opt : options)
        {
            if (value == opt)
            {
                return true;
            }
        }
        return false;
    }

    //! Check if a given enum value it not one of the given enums.
    //!
    //! @param value the value to check
    //! @param options the options to comare to
    //! @returns false if the value matches one of the options
    template <typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
    [[nodiscard]] constexpr
    bool none_of(Enum value, std::vector<Enum> options) noexcept
    {
        return !one_of(value, std::move(options));
    }

    template <typename INT>
    constexpr INT bit(INT offset)
    {
        return static_cast<INT>(1) << offset;
    }
}
