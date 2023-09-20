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

#include "opengl.h"
#include "utils.h"

struct FIBITMAP;

namespace pkzo
{
    //! Color Format
    enum class ColorMode
    {
        UNKNOWN = 0,
        R       = to_underlying(opengl::ColorMode::R),
        RG      = to_underlying(opengl::ColorMode::RG),
        RGB     = to_underlying(opengl::ColorMode::RGB),
        BGR     = to_underlying(opengl::ColorMode::BGR),
        RGBA    = to_underlying(opengl::ColorMode::RGBA),
        BGRA    = to_underlying(opengl::ColorMode::BGRA)
    };

    //! Data Type
    enum class DataType
    {
        UNKNOWN = 0,
        INT8    = to_underlying(opengl::DataType::BYTE),
        UINT8   = to_underlying(opengl::DataType::UNSIGNED_BYTE),
        INT16   = to_underlying(opengl::DataType::SHORT),
        UINT16  = to_underlying(opengl::DataType::UNSIGNED_SHORT),
        INT32   = to_underlying(opengl::DataType::INT),
        UINT32  = to_underlying(opengl::DataType::UNSIGNED_INT),
        FLOAT   = to_underlying(opengl::DataType::FLOAT),
        DOUBLE  = to_underlying(opengl::DataType::DOUBLE)
    };

    using opengl::FilterMode;
    using opengl::WrapMode;

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
        //! Load a texture from file.
        static TexturePtr load(const std::filesystem::path& file);
        //! Load a texture from memory buffer
        //!
        //! This function loads a compressed image (i.e. jpeg format) from a memoy buffer.
        static TexturePtr load_memory(Format format, const void* data, size_t size);
        //! Create an immage from a color buffer.
        //!
        //! This function loads an uncompressed image (i.e. raw RBGA data) for a buffer.
        static TexturePtr create_from_buffer(const glm::uvec2& size, ColorMode mode, DataType group, const void* memory, const std::string& label = "memory");

        explicit Texture(const std::filesystem::path& file);
        explicit Texture(const glm::uvec2& size, ColorMode mode, DataType group, const void* memory, const std::string& label = "memory");
        explicit Texture(Format format, const void* data, size_t size);
        ~Texture();

        //! Get the debug label.
        const std::string& get_label() const noexcept;

        //! Get the file, if any.
        const std::filesystem::path& get_file() const noexcept;

        //! Get the size.
        glm::uvec2 get_size() const noexcept;
        //! Get the color mode.
        ColorMode get_color_mode() const noexcept;
        //! Get the data type.
        DataType get_data_type() const noexcept;

        //! Read a texel.
        glm::vec4 get_texel(const glm::uvec2& index) const noexcept;
        //! Set a texel.
        void set_texel(const glm::uvec2& index, const glm::vec4& value) noexcept;

        //! Get a buffer to the raw bits.
        const void* get_bits() const noexcept;

        //! Set the filter mode.
        void set_filter_mode(FilterMode value) noexcept;
        //! Get the filter mode.
        FilterMode get_filter_mode() const noexcept;

        //! Set the wrap mode.
        void set_wrap_mode(WrapMode value) noexcept;
        //! Get the wrap mode.
        WrapMode get_wrap_mode() const noexcept;

        //! Upload to OpenGL
        void upload();

        //! Free OpenGL resource
        void release();
        //! Check if the texture was uploaded.
        bool is_uploaded() const noexcept;
        //! Bind the texture to a given texture slot.
        void bind(glm::uint slot);

        //! Save to file in the fiven format.
        //!
        //! This function will save the texture to file. The file's
        //! extention will determine the format it will be saved in.
        void save(const std::filesystem::path& file) const;

        //! Get a deep hash of the image data.
        //!
        //! @note std::hash is implemented for Texture and shared_ptr<Texture> using get_hash
        size_t get_hash() const noexcept;

    private:
        std::filesystem::path          file;
        std::string                    label       = "unnamed";
        FIBITMAP*                      bitmap      = nullptr;
        FilterMode                     filter_mode = FilterMode::LINEAR;
        WrapMode                       wrap_mode   = WrapMode::REPEAT;

        std::unique_ptr<opengl::Texture> gl_texture;

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

