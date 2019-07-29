// pkzo
// Copyright 2019 Sean Farrell <sean.farrell@rioki.org>

#include "pch.h"
#include "dbg.h"

#include <windows.h>
#include <stdio.h>
#include <intrin.h>
#include <dbghelp.h>
#include <array>
#include <gl/glew.h>

#pragma comment(lib, "dbghelp.lib")

namespace pkzo
{
    std::ostream& operator << (std::ostream& os, TraceLevel level)
    {
        switch (level)
        {
            case TraceLevel::TRACE_ERROR:
                os << "ERROR";
                break;
            case TraceLevel::TRACE_WARNING:
                os << "WARNING";
                break;
            case TraceLevel::TRACE_INFO:
                os << "INFO";
                break;
        }
        return os;
    }

    void trace(const std::string_view func, TraceLevel level, const std::string_view msg)
    {
        std::stringstream buff;
        buff << level << " " << func << ": msg\n";
        OutputDebugStringA(buff.str().data());
    }

    std::string basename(const std::string& file)
    {
        size_t i = file.find_last_of("\\/");
        if (i == std::string::npos)
        {
            return file;
        }
        else
        {
            return file.substr(i + 1);
        }
    }

    std::vector<StackFrame> trace_stack()
    {
        #if _WIN64
        DWORD machine = IMAGE_FILE_MACHINE_AMD64;
        #else
        DWORD machine = IMAGE_FILE_MACHINE_I386;
        #endif
        HANDLE process = GetCurrentProcess();
        HANDLE thread  = GetCurrentThread();

        if (SymInitialize(process, NULL, TRUE) == FALSE)
        {
            return std::vector<StackFrame>();
        }

        SymSetOptions(SYMOPT_LOAD_LINES);

        CONTEXT context = {};
        context.ContextFlags = CONTEXT_FULL;
        RtlCaptureContext(&context);

        #if _WIN64
        STACKFRAME frame = {};
        frame.AddrPC.Offset = context.Rip;
        frame.AddrPC.Mode = AddrModeFlat;
        frame.AddrFrame.Offset = context.Rbp;
        frame.AddrFrame.Mode = AddrModeFlat;
        frame.AddrStack.Offset = context.Rsp;
        frame.AddrStack.Mode = AddrModeFlat;
        #else
        STACKFRAME frame = {};
        frame.AddrPC.Offset = context.Eip;
        frame.AddrPC.Mode = AddrModeFlat;
        frame.AddrFrame.Offset = context.Ebp;
        frame.AddrFrame.Mode = AddrModeFlat;
        frame.AddrStack.Offset = context.Esp;
        frame.AddrStack.Mode = AddrModeFlat;
        #endif

        bool first = true;

        std::vector<StackFrame> frames;
        while (StackWalk(machine, process, thread, &frame, &context , NULL, SymFunctionTableAccess, SymGetModuleBase, NULL))
        {
            StackFrame f = {};
            f.address = frame.AddrPC.Offset;

            #if _WIN64
            DWORD64 moduleBase = 0;
            #else
            DWORD moduleBase = 0;
            #endif

            moduleBase = SymGetModuleBase(process, frame.AddrPC.Offset);

            char moduelBuff[MAX_PATH];
            if (moduleBase && GetModuleFileNameA((HINSTANCE)moduleBase, moduelBuff, MAX_PATH))
            {
                f.module = basename(moduelBuff);
            }
            else
            {
                f.module = "Unknown Module";
            }
            #if _WIN64
            DWORD64 offset = 0;
            #else
            DWORD offset = 0;
            #endif
            char symbolBuffer[sizeof(IMAGEHLP_SYMBOL) + 255];
            PIMAGEHLP_SYMBOL symbol = (PIMAGEHLP_SYMBOL)symbolBuffer;
            symbol->SizeOfStruct = (sizeof IMAGEHLP_SYMBOL) + 255;
            symbol->MaxNameLength = 254;

            if (SymGetSymFromAddr(process, frame.AddrPC.Offset, &offset, symbol))
            {
                f.name = symbol->Name;
            }
            else
            {
                f.name = "Unknown Function";
            }

            IMAGEHLP_LINE line;
            line.SizeOfStruct = sizeof(IMAGEHLP_LINE);

            DWORD offset_ln = 0;
            if (SymGetLineFromAddr(process, frame.AddrPC.Offset, &offset_ln, &line))
            {
                f.file = line.FileName;
                f.line = line.LineNumber;
            }
            else
            {
                f.line = 0;
            }

            if (!first)
            {
                frames.push_back(f);
            }
            first = false;
        }

        SymCleanup(process);

        return frames;
    }

    void handle_assert(const std::string_view func, const std::string_view cond)
    {
        std::stringstream buff;
        buff << "Assertion '" << cond << "' failed! \n";
        trace(func, TraceLevel::TRACE_ERROR, buff.str());

        int r = MessageBoxA(NULL, buff.str().c_str(), "General Software Fault", MB_ABORTRETRYIGNORE|MB_ICONSTOP);
        if (r == IDABORT)
        {
            throw_with_callstack<std::logic_error>(func, buff.str());
        }
        if (r == IDRETRY)
        {
            DebugBreak();
        }
    }

    std::string glerror_string(GLenum error)
    {
        switch (error)
        {
            case GL_NO_ERROR:
                return "GL_NO_ERROR";
            case GL_INVALID_ENUM:
                return "GL_INVALID_ENUM";
            case GL_INVALID_VALUE:
                return "GL_INVALID_VALUE";
            case GL_INVALID_OPERATION:
                return "GL_INVALID_OPERATION";
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                return "GL_INVALID_FRAMEBUFFER_OPERATION";
            case GL_OUT_OF_MEMORY:
                return "GL_OUT_OF_MEMORY";
            default:
                return "Unknown glError ID";
        }
    }

    void check_opengl(const std::string_view func, unsigned int error)
    {
        if (error != GL_NO_ERROR)
        {
            handle_assert(func, glerror_string(error));
        }
    }
}