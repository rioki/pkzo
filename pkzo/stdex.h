// A little collection of things that sould be standard.
// Copyright 2011-2019 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.

#ifndef _STDEX_H_
#define _STDEX_H_

#include <cassert>
#include <memory>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <sstream>
#include <fstream>

namespace stdex
{
    class non_copyable
    {
    public:
        non_copyable() = default;
        non_copyable(const non_copyable&) = delete;
        ~non_copyable() = default;
        non_copyable& operator = (const non_copyable&) = delete;
    };

    template <typename... Args>
    void noop(Args...) {}

    template <typename T>
    std::shared_ptr<T> wrap_shared(T* object)
    {
        return std::shared_ptr<T>(object, noop<T*>);
    }

    template <typename T>
    std::shared_ptr<T> wrap_shared(T& object)
    {
        return wrap_shared(&object);
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

    inline
    std::string read_file(const std::filesystem::path& file)
    {
        if (!std::filesystem::exists(file))
        {
            throw std::runtime_error("File " + file.string() + " does not exist.");
        }

        auto result = std::string{};
        auto size = std::filesystem::file_size(file);
        result.resize(size + 1);
        auto fs = std::ifstream{file, std::ios::binary};
        fs.read(result.data(), size);

        if (fs.gcount() != size)
        {
            throw std::runtime_error("Failed to read " + file.string() + " .");
        }
        return result;
    }

    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    template<typename E>
    constexpr auto to_int(E e) -> typename std::underlying_type<E>::type
    {
       return static_cast<typename std::underlying_type<E>::type>(e);
    }
}

#define STDEX_BIT(n) (1 << n)
#define STDEX_ENUM_BIT_OPERATORS(ENUM) \
        constexpr ENUM operator | (ENUM rhs, ENUM lhs) \
        { \
            return static_cast<ENUM>(::stdex::to_int(rhs) | ::stdex::to_int(lhs)); \
        } \
        constexpr ENUM operator & (ENUM rhs, ENUM lhs) \
        { \
            return static_cast<ENUM>(::stdex::to_int(rhs) & ::stdex::to_int(lhs)); \
        } \
        constexpr ENUM operator ^ (ENUM rhs, ENUM lhs) \
        { \
            return static_cast<ENUM>(::stdex::to_int(rhs) ^ ::stdex::to_int(lhs)); \
        } \
        constexpr ENUM operator >> (ENUM rhs, int n) \
        { \
            return static_cast<ENUM>(::stdex::to_int(rhs) >> n); \
        } \
        constexpr ENUM operator << (ENUM rhs, int n) \
        { \
            return static_cast<ENUM>(::stdex::to_int(rhs) << n); \
        } \
        constexpr ENUM operator ~ (ENUM val) \
        { \
            return static_cast<ENUM>(~ ::stdex::to_int(val)); \
        }

#endif
