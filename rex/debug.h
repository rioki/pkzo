// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <source_location>
#include <string_view>
#include <functional>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#include <dbghelp.h>
#undef ERROR
#endif

#include "defines.h"
#include "tinyformat.h"

namespace rex
{
    //! Check if the current execution is done inside a debugger.
    REX_EXPORT bool check_debugger() noexcept;

    //! Emit debugger break.
    REX_EXPORT void debug_break();

    //! Write crash dump to temporary folder.
    REX_EXPORT void write_crash_dump() noexcept;

    using trace_fun = std::function<void (const std::string_view&)>;

    //! Set the trace handler.
    //!
    //! The trace handler is the function that actually implements the trace.
    //!
    //! @param handler The new trace handler.
    //! @return The old trace handler.
    REX_EXPORT trace_fun set_trace_handler(trace_fun handler) noexcept;

    //! Trace a message.
    //!
    //! The trace dunction is used to trace a message. The trace handler is called.
    //! The default trace handler will print the message to std::cerr or OutputDebugString.
    //!
    //! You can use the printf syntax to format the message.
    //!
    //! @param message Either a plain message or a format string.
    //! @param args Arguments to be proivded to the format string.
    //!
    //! @{
    REX_EXPORT void trace(const std::string_view& message) noexcept;

    template <typename... Args>
    void trace(const std::string_view& message, Args&&... args) noexcept
    {
        trace(tfm::format(message.data(), std::forward<Args>(args)...));
    }
    //! @}

    using fail_fun  = std::function<void ()>;

    //! Set the fail handler.
    //!
    //! The failhandler is called when a check fails or when fail is called.
    //!
    //! @param handler The new fail handler.
    //! @return The old fail handler.
    REX_EXPORT fail_fun set_fail_handler(fail_fun handler) noexcept;

    //! Check a condition.
    //!
    //! The check macro is used to check a condition, like assert. If the
    //! condition is false the fail handler is called. The default fail handler
    //! will call std::terminate.
    //!
    //! @param condition The condition to check.
    //! @param location The location of the check.
    REX_EXPORT void check_impl(bool condition, const std::source_location& location) noexcept;

    template <typename T>
    void check(const T& condition, const std::source_location& location = std::source_location::current()) noexcept
    {
        check_impl(static_cast<bool>(condition), location);
    }

    //! Signal a unrecoverable condition.
    //!
    //! The fail macro is used to signal a unrecoverable condition. The fail
    //! handler is called. The default fail handler will call std::terminate.
    [[noreturn]]
    REX_EXPORT void fail(const std::source_location& location = std::source_location::current()) noexcept;

    constexpr void no_check() noexcept {}

    //! Crash Handler
    //!
    //! The crash handler will install a callback into the OS and should a crash ocur,
    //! it will pull a crash dump for later analysis. If it can detect a debugger it
    //! will try to break into the debugger.
    class REX_EXPORT crash_handler
    {
    public:
        explicit crash_handler(const std::function<void ()>& cb) noexcept;
        crash_handler(const crash_handler&) = delete;
        ~crash_handler();
        crash_handler& operator = (const crash_handler&) = delete;

    private:
        std::function<void ()> crash_cb;

        #ifdef _WIN32
        LPTOP_LEVEL_EXCEPTION_FILTER old_exception_filter;
        friend LONG WINAPI handle_crash(EXCEPTION_POINTERS* exp);
        #endif
    };
}

#ifdef NDEBUG
#define debug_check no_check
#else
#define debug_check check
#endif
