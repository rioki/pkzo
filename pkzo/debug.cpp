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

#include "debug.h"

#include <format>
#include <array>
#include <filesystem>

#ifdef _WIN32
#include <DbgHelp.h>
#endif

namespace pkzo
{
    std::string basename(const std::string& file) noexcept
    {
        auto i = file.find_last_of("\\/");
        if (i == std::string::npos)
        {
            return file;
        }
        else
        {
            return file.substr(i + 1);
        }
    }

    std::string funcname(const std::string& func) noexcept
    {
        auto s = func.find_last_of(":");
        auto e = func.find_first_of("(");

        if (s == std::string::npos)
        {
            s = 0u;
        }
        else
        {
            s = s + 1;
        }
        if (e == std::string::npos)
        {
            e = func.size();
        }
        else
        {
            e = e;
        }

        return func.substr(s, e - s);
    }

    void trace(const std::string_view message, const std::source_location location) noexcept
    {
        const auto line = std::format("{}({}): {}: {}\n", basename(location.file_name()), location.line(), funcname(location.function_name()), message);
        #ifdef _WIN32
        OutputDebugStringA(line.c_str());
        #else
        std::cerr << line;
        #endif
    }

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

    std::string get_env_variable(const std::string_view name) noexcept
    {
        auto buffer = std::array<char, MAX_PATH>{};
        auto len    = size_t{0};

        const auto err = getenv_s(&len, buffer.data(), buffer.size(), name.data());
        if (err == 0) // was found
        {
            return std::string(buffer.data(), len);
        }

        return {};
    }

    std::filesystem::path get_temp_folder() noexcept
    {
        #ifdef _WIN32
        std::array<wchar_t, MAX_PATH> buff;
        const auto r = GetTempPathW(static_cast<DWORD>(buff.size()), buff.data());
        if (r != 0)
        {
            return buff.data();
        }
        #endif

        return get_env_variable("TEMP");
    }

    std::string get_module_filename()
    {
        #ifdef _WIN32
        auto handle = GetModuleHandleA(NULL);
        if (handle == NULL)
        {
            return "";
        }

        auto buff = std::array<char, MAX_PATH>{};
        auto r = GetModuleFileNameA(handle, buff.data(), static_cast<DWORD>(buff.size()));
        if (r == 0)
        {
            return "";
        }

        return std::string(buff.data(), r);
        #endif
        return "";
    }

    std::filesystem::path create_crash_dump_name() noexcept
    {
        const auto time     = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
        const auto exe_name = basename(get_module_filename());
        auto filename = std::format("{}.{:%Y-%m-%d_%H-%M-%S}.dmp", exe_name, time);
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
            trace(std::format("Failed to open {} for writing: {}", filename.string(), GetLastErrorString()));
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
            trace(std::format("Failed to write mini dump to {}", filename.string()));
        }

        CloseHandle(handle);
    }
    #endif

    void write_crash_dump() noexcept
    {
        #ifdef _WIN32
        write_crash_dump_win32(create_crash_dump_name());
        #else
        trace("write_crash_dump not implemented for this platform.");
        #endif
    }

    void fail(const std::string_view msg, const std::source_location location) noexcept
    {
        trace(msg, location);

        if (check_debugger())
        {
            debug_break();
        }

        write_crash_dump();

        std::terminate();
    }

    void check(bool condition, const std::string_view msg, const std::source_location location) noexcept
    {
        if (! condition)
        {
            fail(msg, location);
        }
    }

    LONG WINAPI handle_crash(EXCEPTION_POINTERS* exp)
    {
        if (check_debugger())
        {
            debug_break();
        }
        else
        {
            auto path = create_crash_dump_name();
            trace(std::format("Applicaiton crashed. Writing crash dump to {}", path.string()));
            write_crash_dump_win32(path, exp);
        }
        return EXCEPTION_EXECUTE_HANDLER;
    }

    CrashHandler::CrashHandler()
    {
        old_exception_filter = SetUnhandledExceptionFilter(handle_crash);
    }

    CrashHandler::~CrashHandler()
    {
        SetUnhandledExceptionFilter(old_exception_filter);
    }
}