// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"
#include "debug.h"

#include "env.h"

namespace rex
{
    bool check_debugger() noexcept
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

    std::filesystem::path create_crash_dump_name() noexcept
    {
        const auto exe_name = file_name(get_module_filename());
        auto time = std::chrono::system_clock::now().time_since_epoch().count();
        auto filename = tfm::format("%s.%s.dmp", exe_name, time);
        return get_temp_folder() / filename;
    }

    #ifdef _WIN32
    MINIDUMP_EXCEPTION_INFORMATION GetExceptionInfo(EXCEPTION_POINTERS* exceptionPointers) noexcept
    {
        auto exceptionInfo = MINIDUMP_EXCEPTION_INFORMATION{};
        exceptionInfo.ThreadId          = GetCurrentThreadId();
        exceptionInfo.ExceptionPointers = exceptionPointers;
        exceptionInfo.ClientPointers    = TRUE;
        return exceptionInfo;
    }

    std::string GetErrorMessage(int32_t errorid) noexcept
    {
        auto buffer = std::array<char, 1024>{};
        auto landId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
        auto flags = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
        auto stringSize = FormatMessageA(flags, NULL, errorid, landId, buffer.data(), static_cast<DWORD>(buffer.size()), NULL);
        return std::string(buffer.data(), stringSize);
    }

    std::string GetLastErrorString() noexcept
    {
        auto error = ::GetLastError();
        return GetErrorMessage(error);
    }

    void write_crash_dump_win32(const std::filesystem::path& filename, EXCEPTION_POINTERS* exceptionPointers = nullptr) noexcept
    {
        const auto handle = CreateFileW(filename.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (handle == INVALID_HANDLE_VALUE)
        {
            trace("Failed to open %s for writing: %s", filename, GetLastErrorString());
            return;
        }

        const auto process   = GetCurrentProcess();
        const auto processId = GetCurrentProcessId();


        auto result = FALSE;
        if (exceptionPointers != nullptr)
        {
            auto exceptionInfo   = GetExceptionInfo(exceptionPointers);
            result = MiniDumpWriteDump(process, processId, handle, MiniDumpNormal, &exceptionInfo, 0, 0);
        }
        else
        {
            result = MiniDumpWriteDump(process, processId, handle, MiniDumpNormal, nullptr, 0, 0);
        }

        if (result == FALSE)
        {
            trace("Failed to write mini dump to %s", filename);
        }

        CloseHandle(handle);
    }
    #endif

    void write_crash_dump() noexcept
    {
        #ifdef _WIN32
        write_crash_dump_win32(create_crash_dump_name());
        #else
        #error Port Me
        #endif
    }

    void default_trace_handler(const std::string_view& message) noexcept
    {
        #ifdef _WIN32
        OutputDebugStringA(message.data());
        OutputDebugStringA("\n");
        #else
        std::cerr << message << std::endl;
        #endif
    }

    trace_fun trace_handler = default_trace_handler;

    trace_fun set_trace_handler(trace_fun handler) noexcept
    {
        assert(handler != nullptr);
        auto old_hanlder = trace_handler;
        trace_handler = handler;
        return old_hanlder;
    }

    void trace(const std::string_view& message) noexcept
    {
        trace_handler(message);
    }

    fail_fun fail_handler = std::terminate;

    fail_fun set_fail_handler(fail_fun handler) noexcept
    {
        assert(handler != nullptr);
        auto old_hanlder = fail_handler;
        fail_handler = handler;
        return old_hanlder;
    }

    void check_impl(bool condition, const std::source_location& location) noexcept
    {
        if (!condition)
        {
            trace("%s(%d): %s: Check failed.", file_name(location.file_name()), location.line(), location.function_name());
            fail_handler();
        }
    }

    void fail(const std::source_location& location) noexcept
    {
        trace(tfm::format("%s(%d): %s: Unexpected code path.", file_name(location.file_name()), location.line(), location.function_name()));
        fail_handler();
    }

    crash_handler* crash_handler_instance = nullptr;

    LONG WINAPI handle_crash(EXCEPTION_POINTERS* exp)
    {
        assert(crash_handler_instance != nullptr);
        assert(crash_handler_instance->crash_cb != nullptr);
        crash_handler_instance->crash_cb();
        return EXCEPTION_EXECUTE_HANDLER;
    }

    crash_handler::crash_handler(const std::function<void ()>& cb) noexcept
    : crash_cb(cb)
    {
        assert(crash_handler_instance == nullptr);
        assert(crash_cb != nullptr);
        crash_handler_instance = this;
        old_exception_filter = SetUnhandledExceptionFilter(handle_crash);
    }

    crash_handler::~crash_handler()
    {
        SetUnhandledExceptionFilter(old_exception_filter);
        crash_handler_instance = nullptr;
    }
}
