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

#include <memory>
#include <filesystem>
#include <glm/glm.hpp>

struct FIBITMAP;

namespace pkzo
{
    //! Color Format
    enum class ColorMode
    {
        UNKNOWN,
        R,
        RG,
        RGB,
        BGR,
        RGBA,
        BGRA
    };

    //! Data Type
    enum class DataType
    {
        UNKNOWN,
        INT8,
        UINT8,
        INT16,
        UINT16,
        UINT32,
        INT32,
        FLOAT,
        DOUBLE
    };

    //! Filter Mode
    enum class FilterMode
    {
        NEAREST,
        LINEAR
    };

    //! Wrap Mode
    enum class WrapMode
    {
        CLAMP,
        REPEAT
    };

    // Matches FREE_IMAGE_FORMAT
    enum class Format
    {
        UNKNOWN = -1,
        BMP     = 0,
        ICO     = 1,
        JPEG    = 2,
        JNG     = 3,
        KOALA   = 4,
        LBM     = 5,
        IFF     = LBM,
        MNG     = 6,
        PBM     = 7,
        PBMRAW  = 8,
        PCD     = 9,
        PCX     = 10,
        PGM     = 11,
        PGMRAW  = 12,
        PNG     = 13,
        PPM     = 14,
        PPMRAW  = 15,
        RAS     = 16,
        TARGA   = 17,
        TIFF    = 18,
        WBMP    = 19,
        PSD     = 20,
        CUT     = 21,
        XBM     = 22,
        XPM     = 23,
        DDS     = 24,
        GIF     = 25,
        HDR     = 26,
        FAXG3   = 27,
        SGI     = 28,
        EXR     = 29,
        J2K     = 30,
        JP2     = 31,
        PFM     = 32,
        PICT    = 33,
        RAW     = 34,
        WEBP    = 35,
        JXR     = 36
    };

    class Texture;
    using TexturePtr = std::shared_ptr<Texture>;

    //! 2D Image
    class PKZO_EXPORT Texture
    {
    public:
        static TexturePtr load(const std::filesystem::path& file);
        static TexturePtr load_memory(Format format, const void* data, size_t size);
        static TexturePtr create_from_buffer(const glm::uvec2& size, ColorMode mode, DataType group, const void* memory, const std::string& label = "memory");

        explicit Texture(const std::filesystem::path& file);
        explicit Texture(const glm::uvec2& size, ColorMode mode, DataType group, const void* memory, const std::string& label = "memory");
        explicit Texture(Format format, const void* data, size_t size);
        ~Texture();

        const std::string& get_label() const noexcept;

        const std::filesystem::path& get_file() const noexcept;

        glm::uvec2 get_size() const noexcept;
        ColorMode get_color_mode() const noexcept;
        DataType get_data_type() const noexcept;

        glm::vec4 get_texel(const glm::uvec2& index) const noexcept;
        void set_texel(const glm::uvec2& index, const glm::vec4& value) noexcept;

        const void* get_bits() const noexcept;

        void set_filter_mode(FilterMode value) noexcept;
        FilterMode get_filter_mode() const noexcept;

        void set_wrap_mode(WrapMode value) noexcept;
        WrapMode get_wrap_mode() const noexcept;

        void save(const std::filesystem::path& file) const;

        size_t get_hash() const noexcept;

    private:
        std::filesystem::path          file;
        std::string                    label       = "unnamed";
        FIBITMAP*                      bitmap      = nullptr;
        FilterMode                     filter_mode = FilterMode::LINEAR;
        WrapMode                       wrap_mode   = WrapMode::REPEAT;

        Texture(const Texture&) = delete;
        Texture& operator = (const Texture&) = delete;
    };

    PKZO_EXPORT float compare(const std::shared_ptr<Texture>& a, const std::shared_ptr<Texture>& b);
    PKZO_EXPORT std::shared_ptr<Texture> diff(const std::shared_ptr<Texture>& a, const std::shared_ptr<Texture>& b);
}

namespace std
{
    template <>
    struct hash<pkzo::Texture>
    {
        size_t operator () (const pkzo::Texture& v) const noexcept
        {
            return v.get_hash();
        };
    };

    template <>
    struct hash<pkzo::TexturePtr>
    {
        size_t operator () (const pkzo::TexturePtr& v) const noexcept
        {
            return v->get_hash();
        };
    };
}

