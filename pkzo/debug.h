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

#include <string_view>
#include <source_location>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace pkzo
{
    PKZO_EXPORT
    void trace(const std::string_view msg, const std::source_location location = std::source_location::current()) noexcept;

    PKZO_EXPORT
    void check(bool condition, const std::string_view msg = "Check failed.", const std::source_location location = std::source_location::current()) noexcept;

    [[ noreturn ]] PKZO_EXPORT
    void fail(const std::string_view msg = "Unexpected failure.", const std::source_location location = std::source_location::current()) noexcept;

    class PKZO_EXPORT CrashHandler
    {
    public:
        CrashHandler();
        CrashHandler(const CrashHandler&) = delete;
        ~CrashHandler();
        CrashHandler& operator = (const CrashHandler&) = delete;
    private:
        LPTOP_LEVEL_EXCEPTION_FILTER old_exception_filter;
    };
}

