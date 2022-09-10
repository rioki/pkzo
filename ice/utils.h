// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <string>
#include <string_view>
#include <utility>
#include <memory>
#include <ranges>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
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

    template <typename ValueT, typename ContainerT, typename ... Args> inline
    ValueT* add_unique_ptr(ContainerT& container, Args&& ... args) noexcept(std::is_nothrow_constructible_v<ValueT>)
    {
        auto value = std::make_unique<ValueT>(std::forward<Args>(args)...);
        auto ptr = value.get();
        container.push_back(std::move(value));
        return ptr;
    }

    template <typename ValueT, typename ContainerT>
    void remove_unique_ptr(ContainerT& container, ValueT* value)
    {
        assert(value != nullptr);
        auto i = std::ranges::find_if(container, [value] (const auto& ptr) {
            return ptr.get() == value;
        });
        assert(i != end(container));
        container.erase(i);
    }

    ICE_EXPORT std::string join(const std::vector<std::string>& strs, const std::string& delimiter) noexcept;

    ICE_EXPORT std::vector<std::string> explode(const std::string& str, const std::string& delimiter) noexcept;

    ICE_EXPORT std::vector<std::string> tokenize(const std::string& str) noexcept;

    inline
    glm::vec3 rgb(float r, float g, float b)
    {
        return { r, g, b };
    }

    inline
    glm::vec3 rgb(unsigned int r, unsigned int g, unsigned int b)
    {
        return rgb((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f);
    }

    inline
    glm::vec3 rgb(unsigned int hex)
    {
        unsigned int r = (hex & 0x00FF0000) >> 16;
        unsigned int g = (hex & 0x0000FF00) >> 8;
        unsigned int b = (hex & 0x000000FF) >> 0;
        return rgb(r, g, b);
    }

    inline
    glm::vec4 rgba(float r, float g, float b, float a)
    {
        return { r, g, b, a };
    }

    inline
    glm::vec4 rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
    {
        return rgba((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f);
    }

    inline
    glm::vec4 rgba(unsigned int hex)
    {
        unsigned int r = (hex & 0xFF000000) >> 24;
        unsigned int g = (hex & 0x00FF0000) >> 16;
        unsigned int b = (hex & 0x0000FF00) >> 8;
        unsigned int a = (hex & 0x000000FF) >> 0;
        return rgba(r, g, b, a);
    }
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
