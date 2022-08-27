// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <string>
#include <string_view>
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace ice
{
    template <typename T>
    std::string to_string(const T& value)
    {
        auto buff = std::stringstream{};
        buff << value;
        return buff.str();
    }

    template <typename T>
    T from_string(const std::string_view value)
    {
        auto buff = std::stringstream{value};
        auto value = T{};
        buff >> value;
        return value;
    }

    constexpr unsigned int hash(const char* str, int h = 0)
    {
        return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
    }

    inline unsigned int hash(const std::string& str)
    {
        return hash(str.data());
    }
}

#define ICE_SERIALIZE_ENUM(ENUM, ...)                                                           \
    inline std::ostream& operator << (std::ostream& os, const ENUM& e)                          \
    {                                                                                           \
        static_assert(std::is_enum<ENUM>::value, #ENUM " must be an enum!");                    \
        static const std::pair<ENUM, std::string_view> m[] = __VA_ARGS__;                       \
        auto it = std::find_if(begin(m), end(m), [&](const auto& p) {                           \
            return p.first == e;                                                                \
        });                                                                                     \
        if (it != end(m))                                                                       \
        {                                                                                       \
            os << it->second;                                                                   \
        }                                                                                       \
        return os;                                                                              \
    }                                                                                           \
    inline std::istream& operator >> (std::istream& is, ENUM& e)                                \
    {                                                                                           \
        static_assert(std::is_enum<ENUM>::value, #ENUM " must be an enum!");                    \
        static const std::pair<ENUM, std::string_view> m[] = __VA_ARGS__;                       \
        auto word = std::string{};                                                              \
        is >> word;                                                                             \
        auto it = std::find_if(begin(m), end(m), [&](const auto& p) {                           \
            return p.second == word;                                                            \
        });                                                                                     \
        if (it != end(m))                                                                       \
        {                                                                                       \
            e = it->first;                                                                      \
        }                                                                                       \
        else                                                                                    \
        {                                                                                       \
            throw std::runtime_error(std::format("{} is not a {}", word, #ENUM));               \
        }                                                                                       \
        return is;                                                                              \
    }                                                                                           \
    NLOHMANN_JSON_SERIALIZE_ENUM(ENUM, __VA_ARGS__)
