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

#include <stdexcept>
#include <functional>
#include <string_view>
#include <source_location>

#include <tinyformat.h>
#include <rsig/rsig.h>

#include "api.h"

namespace pkzo
{
    constexpr std::string_view basename(const std::string_view file)
    {
        auto i = file.find_last_of("\\/");
        if (i == std::string_view::npos)
        {
            return file;
        }
        else
        {
            return file.substr(i + 1);
        }
    }

    PKZO_EXPORT bool is_debugger_present() noexcept;
    PKZO_EXPORT void debug_break();
    PKZO_EXPORT void debug_output(const std::string_view msg);

    PKZO_EXPORT rsig::connection on_trace(const std::function<void (const std::source_location&, const std::string_view)>& handler);

    PKZO_EXPORT void trace(const std::string_view msg, const std::source_location& loc = std::source_location::current());

    PKZO_EXPORT void check_impl(bool cond, const std::string_view msg, const std::source_location& loc);

    template <typename COND>
    void check(const COND& cond, const std::string_view msg = "Check failed.", const std::source_location& loc = std::source_location::current())
    {
        check_impl(static_cast<bool>(cond), msg, loc);
    }

    template <typename T>
    const std::shared_ptr<T>& safe_ptr(const std::shared_ptr<T>& ptr)
    {
        check(ptr != nullptr, "Pointer is null.");
        return ptr;
    }
}