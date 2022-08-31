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

    inline void hash_combine(std::size_t& seed) {}

    template <typename Car, typename ... Cdr>
    inline void hash_combine(std::size_t& seed, const Car& car, Cdr... cdr)
    {
        std::hash<Car> hasher;
        seed ^= hasher(car) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        hash_combine(seed, cdr...);
    }

    template <typename ... Args>
    inline size_t hash(const Args& ... args)
    {
        size_t seed = 0;
        hash_combine(seed, args...);
        return seed;
    }

    template <typename ContainerT, typename RangeT>
    ContainerT to(RangeT&& range)
    {
        return ContainerT(begin(range), end(range));
    }
    
    ICE_EXPORT std::u32string utf32(const std::string& buff);
    ICE_EXPORT std::u32string utf32(const std::u8string& buff);

    ICE_EXPORT void trace(const std::string_view msg);
}

#define ICE_BIT(n) (1 << n)
#define ICE_ENUM_BIT_OPERATORS(ENUM) \
    constexpr ENUM operator | (ENUM rhs, ENUM lhs) \
    { \
        return static_cast<ENUM>(static_cast<int>(rhs) | static_cast<int>(lhs)); \
    } \
    constexpr ENUM operator & (ENUM rhs, ENUM lhs) \
    { \
        return static_cast<ENUM>(static_cast<int>(rhs) & static_cast<int>(lhs)); \
    } \
    constexpr ENUM operator ^ (ENUM rhs, ENUM lhs) \
    { \
        return static_cast<ENUM>(static_cast<int>(rhs) ^ static_cast<int>(lhs)); \
    } \
    constexpr ENUM operator >> (ENUM rhs, int n) \
    { \
        return static_cast<ENUM>(static_cast<int>(rhs) >> n); \
    } \
    constexpr ENUM operator << (ENUM rhs, int n) \
    { \
        return static_cast<ENUM>(static_cast<int>(rhs) << n); \
    } \
    constexpr ENUM operator ~ (ENUM val) \
    { \
        return static_cast<ENUM>(~ static_cast<int>(val)); \
    } \
    constexpr ENUM& operator |= (ENUM& rhs, ENUM lhs) \
    { \
        return rhs = rhs | lhs; \
    } \
    constexpr ENUM& operator &= (ENUM& rhs, ENUM lhs) \
    { \
        return rhs = rhs & lhs; \
    } \
    constexpr ENUM& operator ^= (ENUM& rhs, ENUM lhs) \
    { \
        return rhs = rhs ^ lhs; \
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
