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

#include <filesystem>

#include <glm/glm.hpp>

#include "api.h"

namespace pkzo
{
    enum class NamedColor
    {
        WHITE,
        BLACK,
        NORMAL
    };

    enum class ColorMode
    {
        MONO,
        RGB,
        BGR,
        RGBA,
        BGRA,
        DEPTH
    };

    enum class DataType
    {
        UNSIGNED_BYTE,
        FLOAT
    };

    enum class TextureFilter
    {
        NEAREST,
        LINEAR,
        LINEAR_MIPMAP
    };

    enum class Clamp
    {
        NO_CLAMP,
        CLAMP_HORIZONTAL,
        CLAMP_VERTICAL,
        CLAMP
    };

    enum class Format
    {
        UNKNOWN,
        JPEG,
        PNG,
        TIFF,
        DDS,
        GIF,
        HDR,
        EXR,
        WEBP
    };

    class PKZO_EXPORT Texture
    {
    public:
        struct FileLoadSpecs
        {
            std::filesystem::path file;
            TextureFilter         filter   = TextureFilter::LINEAR_MIPMAP;
            Clamp                 clamp    = Clamp::NO_CLAMP;
        };

        struct MemorLoadSpecs
        {
            std::string   id       = "unnamed";
            Format        format   = Format::UNKNOWN;
            size_t        size     = 0;
            const void*   memory   = nullptr;
            TextureFilter filter   = TextureFilter::LINEAR_MIPMAP;
            Clamp         clamp    = Clamp::NO_CLAMP;
        };

        struct CreateSpecs
        {
            std::string   id         = "unnamed";
            glm::uvec2    size       = glm::uvec2(0u);
            DataType      data_type  = DataType::UNSIGNED_BYTE;
            ColorMode     color_mode = ColorMode::RGB;
            const void*   memory     = nullptr;
            TextureFilter filter   = TextureFilter::LINEAR_MIPMAP;
            Clamp         clamp    = Clamp::NO_CLAMP;
        };

        static std::shared_ptr<Texture> load_file(const FileLoadSpecs& specs);
        static std::shared_ptr<Texture> load_memory(const MemorLoadSpecs& specs);
        static std::shared_ptr<Texture> create(const CreateSpecs& specs);

        Texture() = default;
        virtual ~Texture() = default;

        virtual const std::string& get_id() const = 0;
        virtual glm::uvec2 get_size() const = 0;
        virtual ColorMode get_color_mode() const = 0;
        virtual DataType get_data_type() const = 0;
        virtual const void* get_memory() const = 0;
        virtual TextureFilter get_filter() const = 0;
        virtual Clamp get_clamp() const = 0;

    private:
        Texture(const Texture&) = delete;
        Texture& operator = (const Texture&) = delete;
    };
}
