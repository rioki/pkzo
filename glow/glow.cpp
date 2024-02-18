// OpenGL Object Wrapper
// Copyright 2016-2023 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "glow.h"

namespace glow
{
    constexpr const char* source_to_string(GLenum source) noexcept
    {
      switch (source) {
        case GL_DEBUG_SOURCE_API:
          return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
          return "Window System";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
          return "Shader Compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY:
          return "Third Party";
        case GL_DEBUG_SOURCE_APPLICATION:
          return "Application";
        case GL_DEBUG_SOURCE_OTHER:
          return "Other";
        default:
          return "Unknown";
      }
    }

    constexpr const char* type_to_string(GLenum type) noexcept
    {
      switch (type) {
        case GL_DEBUG_TYPE_ERROR:
          return "Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
          return "Deprecated Behavior";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
          return "Undefined Behavior";
        case GL_DEBUG_TYPE_PORTABILITY:
          return "Portability";
        case GL_DEBUG_TYPE_PERFORMANCE:
          return "Performance";
        case GL_DEBUG_TYPE_OTHER:
          return "Other";
        case GL_DEBUG_TYPE_MARKER:
          return "Marker";
        case GL_DEBUG_TYPE_PUSH_GROUP:
          return "Push Group";
        case GL_DEBUG_TYPE_POP_GROUP:
          return "Pop Group";
        default:
          return "Unknown";
      }
    }

    constexpr const char* severity_to_string(GLenum severity) noexcept
    {
      switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
          return "High";
        case GL_DEBUG_SEVERITY_MEDIUM:
          return "Medium";
        case GL_DEBUG_SEVERITY_LOW:
          return "Low";
        case GL_DEBUG_SEVERITY_NOTIFICATION:
          return "Notification";
        default:
          return "Unknown";
      }
    }

    void GLAPIENTRY trace_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        {
            return;
        }

        const auto source_str   = source_to_string(source);
        const auto type_str     = type_to_string(type);
        const auto severity_str = severity_to_string(severity);

        auto formatted_message = tfm::format(
            "OpenGL Debug [Source: %s, Type: %s, ID: %s, Severity: %s]: %s",
            source_str, type_str, id, severity_str, message);

        trace(formatted_message);
    }

    void init()
    {
        glewExperimental = GL_TRUE;
        auto result = glewInit();
        if (result != GLEW_OK)
        {
            auto msg = tfm::format("Failed to initialize GLEW: %s", glewGetErrorString(result));
            throw std::runtime_error(msg);
        }

        clear_erorrs();

        #ifndef NDEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(trace_callback, nullptr);
        #endif
    }

    void clear_erorrs() noexcept
    {
        while (glGetError() != GL_NO_ERROR);
    }

    std::string get_error_string(GLenum error) noexcept
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
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";
        default:
            return tfm::format("Unknown OpenGL Error: %#010x", error);
        }
    }

    void check_error(const std::source_location& location)
    {
        auto error = glGetError();
        if (error != GL_NO_ERROR)
        {
            rex::trace(tfm::format("%s(%d): %s: OpenGL Error: %s", rex::file_name(location.file_name()), location.line(), location.function_name(), get_error_string(error)));
            rex::fail(location);
        }
    }

    Section::Section(const std::string_view id)
    {
        #ifndef NDEBUG
        glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, id.data());
        check_error();
        #endif
    }

    Section::~Section()
    {
        #ifndef NDEBUG
        glPopDebugGroup();
        check_error();
        #endif
    }
}
