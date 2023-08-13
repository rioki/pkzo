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

#pragma once
#include "config.h"

#include <functional>
#include <string>
#include <locale>
#include <vector>
#include <filesystem>

namespace pkzo
{
    template <typename T> constexpr
    T make_bit_mask(T i)
    {
        return 1 << i;
    }

    template <typename T>
    std::string to_string(T value)
    {
        std::stringstream buff;
        buff << value;
        return buff.str();
    }

    template <>
    inline std::string to_string(bool value)
    {
        return value ? "true" : "false";
    }

    template <typename T>
    T from_string(const std::string& str)
    {
        std::stringstream buff(str);
        T value;
        buff >> value;
        return value;
    }

    template <>
    inline bool from_string(const std::string& str)
    {
        if (str == "true")
            return true;
        if (str == "false")
            return false;
        throw std::logic_error("No a boolean value");
    }

    constexpr
    unsigned int hash(const char* str, int h = 0)
    {
        return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
    }

    inline
    unsigned int hash(const std::string& str)
    {
        return hash(str.c_str());
    }

    inline void hash_combine(std::size_t& seed) {}

    template <typename Car, typename ... Cdr>
    inline void hash_combine(std::size_t& seed, const Car& car, const Cdr&... cdr)
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

    PKZO_EXPORT
    std::string tolower(const std::string& str, const std::locale& loc = std::locale("C"));

    PKZO_EXPORT
    std::string toupper(const std::string& str, const std::locale& loc = std::locale("C"));

    PKZO_EXPORT
    std::vector<std::byte> load_binary_file(const std::filesystem::path& file);

    PKZO_EXPORT
    std::string load_text_file(const std::filesystem::path& file);
}

// needed for koenig lookup
namespace std
{
    template <typename T>
    std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
    {
        for (auto i = 0u; i < v.size(); i++)
        {
            os << v[i];
            if (i != (v.size() - 1))
            {
                os << ", ";
            }
        }
        return os;
    }
}

#define PKZO_ENUM_OPERATORS(ENUM) \
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
