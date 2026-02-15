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

#include "debug.h"

#if _WIN32
#include <Windows.h>
#include <dbghelp.h>
#endif

#include <tinyformat.h>

#include "api.h"

namespace pkzo
{
    bool is_debugger_present() noexcept
    {
        #ifdef _WIN32
        return IsDebuggerPresent();
        #else
        #error Port Me
        #endif
        return false;
    }


    void debug_break()
    {
        #ifdef _WIN32
        DebugBreak();
        #else
        #error Port Me
        #endif
    }

    void debug_output(const std::string_view msg)
    {
        #ifdef _WIN32
        OutputDebugStringA(msg.data());
        #else
        #error Port Me
        #endif
    }

    std::function<void (const std::source_location&, const std::string_view)> trace_func = [] (const std::source_location& loc, const std::string_view msg)
    {
        auto output = tfm::format("%s(%d): %s\n", basename(loc.file_name()), loc.line(), msg);

        if (is_debugger_present()) debug_output(output);

        std::cerr << output;
    };

    rsig::signal<const std::source_location&, const std::string_view> trace_signal;

    rsig::connection on_trace(const std::function<void (const std::source_location&, const std::string_view)>& handler)
    {
        return trace_signal.connect(handler);
    }

    void trace(const std::string_view msg, const std::source_location& loc)
    {
        trace_signal.emit(loc, msg);
    }

    void check_impl(bool cond, const std::string_view msg, const std::source_location& loc)
    {
        if (cond == false)
        {
            trace(msg, loc);

            if (is_debugger_present()) debug_break();

            throw std::logic_error(std::string(msg));
        }
    }

    void check_arg_impl(bool cond, const std::string_view msg, const std::source_location& loc)
    {
        if (cond == false)
        {
            trace(msg, loc);

            if (is_debugger_present()) debug_break();

            throw std::invalid_argument(std::string(msg));
        }
    }
}