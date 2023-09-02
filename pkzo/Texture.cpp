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

#include "Texture.h"

#include "debug.h"
#include "utils.h"
#include "array_view.h"

#include <GL/glew.h>

// include last, it defines _WINDOWS_ and messes EVERYTHING
#include <FreeImage.h>

namespace pkzo
{
    auto get_texture_id()
    {
        static auto next_id = std::atomic<size_t>{1};
        return ++next_id;
    }

    void free_image_trace(FREE_IMAGE_FORMAT fif, const char *message)
    {
        trace(message);
    }

    TexturePtr Texture::load(const std::filesystem::path& file)
    {
        return std::make_shared<Texture>(file);
    }

    TexturePtr Texture::load_memory(Format format, const void* data, size_t size)
    {
        return std::make_shared<Texture>(format, data, size);
    }

    TexturePtr Texture::create_from_buffer(const glm::uvec2& size, ColorMode mode, DataType group, const void* memory, const std::string& label)
    {
        return std::make_shared<Texture>(size, mode, group, memory, label);
    }

    Texture::Texture(const std::filesystem::path& f)
    : file(f), label(f.filename().string())
    {
        FreeImage_SetOutputMessage(free_image_trace);
        #ifdef _WIN32
        auto fif = FreeImage_GetFileTypeU(file.c_str(), 0);
        bitmap = FreeImage_LoadU(fif, file.c_str(), JPEG_ACCURATE);
        #else
        auto fif = FreeImage_GetFileType(file.c_str(), 0);
        bitmap = FreeImage_Load(fif, file.c_str(), JPEG_ACCURATE);
        #endif
        if (bitmap == nullptr)
        {
            throw std::runtime_error(std::format("Failed to load '{}'.", file.string()));
        }
    }

    auto get_bpp(ColorMode mode, DataType group)
    {
        auto components = 0u;
        switch (mode)
        {
        case ColorMode::R:
            components = 1u;
            break;
        case ColorMode::RG:
            components = 2u;
            break;
        case ColorMode::RGB:
        case ColorMode::BGR:
            components = 3u;
            break;
        case ColorMode::RGBA:
        case ColorMode::BGRA:
            components = 4u;
            break;
        default:
            fail("Unexpected ColorMode");
        }

        switch (group)
        {
        case DataType::INT8:
        case DataType::UINT8:
            return 8u * components;
        case DataType::INT16:
        case DataType::UINT16:
            return 16u * components;
        case DataType::UINT32:
        case DataType::INT32:
        case DataType::FLOAT:
            return 32u * components;
        case DataType::DOUBLE:
            return 64u * components;
        default:
            fail("Unexpected DataType");
        }
    }

    FREE_IMAGE_TYPE fi_type(DataType group)
    {
        switch (group)
        {
        case DataType::INT8:
        case DataType::UINT8:
            return FIT_BITMAP;
        case DataType::INT16:
            return FIT_INT16;
        case DataType::UINT16:
            return FIT_UINT16;
        case DataType::UINT32:
            return FIT_UINT32;
        case DataType::INT32:
            return FIT_INT32;
        case DataType::FLOAT:
            return FIT_FLOAT;
        case DataType::DOUBLE:
            return FIT_DOUBLE;
        default:
            fail("Unexpected image type.");
        }
    }

    unsigned int red_mask(ColorMode mode)
    {
        switch (mode)
        {
        case ColorMode::R:
        case ColorMode::RG:
        case ColorMode::RGB:
        case ColorMode::RGBA:
            return 0x0000FF;
        case ColorMode::BGR:
        case ColorMode::BGRA:
            return 0xFF0000;
        default:
            fail("Unexpected mask.");
        }
    }

    unsigned int green_mask(ColorMode mode)
    {
        switch (mode)
        {
        case ColorMode::R:
            return 0x00;
        case ColorMode::RG:
        case ColorMode::RGB:
        case ColorMode::RGBA:
        case ColorMode::BGR:
        case ColorMode::BGRA:
            return 0x00FF00;
        default:
            fail("Unexpected mask.");
        }
    }

    unsigned int blue_mask(ColorMode mode)
    {
        switch (mode)
        {
        case ColorMode::R:
        case ColorMode::RG:
            return 0x00;
        case ColorMode::RGB:
        case ColorMode::RGBA:
            return 0xFF0000;
        case ColorMode::BGR:
        case ColorMode::BGRA:
            return 0x0000FF;
        default:
            fail("Unexpected mask.");
        }
    }

    Texture::Texture(const glm::uvec2& size, ColorMode mode, DataType group, const void* memory, const std::string& _label)
    : label(_label)
    {
        auto raw    = reinterpret_cast<BYTE*>(const_cast<void*>(memory));
        auto fitype = fi_type(group);
        auto bpp    = get_bpp(mode, group);
        auto Bpp    = bpp / 8u;
        auto rm     = red_mask(mode);
        auto gm     = green_mask(mode);
        auto bm     = blue_mask(mode);
        if (memory != nullptr)
        {
            bitmap = FreeImage_ConvertFromRawBitsEx(TRUE, raw, fitype, size.x, size.y, Bpp * size.x, bpp, rm, gm, bm);
            if (bitmap == nullptr)
            {
                throw std::runtime_error("Failed to convert raw data.");
            }
        }
        else
        {
            bitmap = FreeImage_AllocateT(fitype, size.x, size.y, bpp, rm, gm, bm);
            if (bitmap == nullptr)
            {
                throw std::runtime_error("Failed to convert raw data.");
            }
        }
    }

    Texture::Texture(Format format, const void* data, size_t size)
    {
        auto stream = FreeImage_OpenMemory(reinterpret_cast<BYTE*>(const_cast<void*>(data)), static_cast<DWORD>(size));
        bitmap = FreeImage_LoadFromMemory(static_cast<FREE_IMAGE_FORMAT>(format), stream, JPEG_ACCURATE);
        FreeImage_CloseMemory(stream);

        if (bitmap == nullptr)
        {
            throw std::runtime_error("Failed to load memory");
        }
    }

    Texture::~Texture()
    {
        // bitmap can be nullptr after moving.
        if (bitmap)
        {
            FreeImage_Unload(bitmap);
            bitmap = nullptr;
        }
        release();
    }

    const std::string& Texture::get_label() const noexcept
    {
        return label;
    }

    const std::filesystem::path& Texture::get_file() const noexcept
    {
        return file;
    }

    glm::uvec2 Texture::get_size() const noexcept
    {
        check(bitmap);
        return {FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap)};
    }

    ColorMode Texture::get_color_mode() const noexcept
    {
        check(bitmap);
        switch (FreeImage_GetImageType(bitmap))
        {
        case FIT_BITMAP:
            switch (FreeImage_GetBPP(bitmap))
            {
            case 8:
                return ColorMode::R;
            case 16:
                return ColorMode::RG;
            case 24:
                return ColorMode::BGR;
            case 32:
                return ColorMode::BGRA;
            default:
                fail();
            }
        case FIT_UINT16:
        case FIT_INT16:
        case FIT_UINT32:
        case FIT_INT32:
        case FIT_FLOAT:
        case FIT_DOUBLE:
            return ColorMode::R;
        case FIT_COMPLEX:
            return ColorMode::RG;
        case FIT_RGB16:
        case FIT_RGBF:
            return ColorMode::RGB;
        case FIT_RGBA16:
        case FIT_RGBAF:
            return ColorMode::RGBA;
        default:
            fail();
        }
    }

    DataType Texture::get_data_type() const noexcept
    {
        check(bitmap);
        switch (FreeImage_GetImageType(bitmap))
        {
        case FIT_BITMAP:
            return DataType::UINT8;
        case FIT_UINT16:
        case FIT_RGB16:
        case FIT_RGBA16:
            return DataType::UINT16;
        case FIT_INT16:
            return DataType::INT16;
        case FIT_UINT32:
            return DataType::UINT32;
        case FIT_INT32:
            return DataType::INT32;
        case FIT_FLOAT:
        case FIT_RGBF:
        case FIT_RGBAF:
            return DataType::FLOAT;
        case FIT_DOUBLE:
        case FIT_COMPLEX:
            return DataType::DOUBLE;
        default:
            fail();
        }
    }

    constexpr bool has_alpha(ColorMode cm)
    {
        switch (cm)
        {
        case ColorMode::RGBA:
        case ColorMode::BGRA:
            return true;
        default:
            return false;
        }
    }

    glm::vec4 Texture::get_texel(const glm::uvec2& index) const noexcept
    {
        check(bitmap != nullptr);

        auto type = FreeImage_GetImageType(bitmap);
        switch (type)
        {
            case FIT_UNKNOWN:
                fail("Unexpected enum value.");
            case FIT_BITMAP:
            {
                RGBQUAD px;
                FreeImage_GetPixelColor(bitmap, index.x, index.y, &px);
                return glm::vec4(static_cast<float>(px.rgbRed)/255.0f, static_cast<float>(px.rgbGreen)/255.0f, static_cast<float>(px.rgbBlue)/255.0f, 1.0f);
            }
            case FIT_FLOAT:
            {
                auto data = reinterpret_cast<float*>(FreeImage_GetBits(bitmap));
                auto i = index.x + index.y * FreeImage_GetWidth(bitmap);
                return glm::vec4(data[i], data[i], data[i], 1.0f);
            }

            case FIT_RGBF:
            {
                auto data = reinterpret_cast<float*>(FreeImage_GetBits(bitmap));
                auto i = index.x * 3 + index.y * FreeImage_GetWidth(bitmap) * 3;
                return glm::vec4(data[i+0], data[i+1], data[i+2], 1.0f);
            }
            case FIT_RGBAF:
            {
                auto data = reinterpret_cast<float*>(FreeImage_GetBits(bitmap));
                auto i = index.x * 4 + index.y * FreeImage_GetWidth(bitmap) * 4;
                return glm::vec4(data[i+0], data[i+1], data[i+2], data[i+3]);
            }
            default:
                fail();
        }

    }

    void Texture::set_texel(const glm::uvec2& index, const glm::vec4& value) noexcept
    {
        auto type = FreeImage_GetImageType(bitmap);
        switch (type)
        {
            case FIT_UNKNOWN:
                fail("Unexpected enum value.");
                break;
            case FIT_BITMAP:
            {
                auto color = RGBQUAD{static_cast<BYTE>(value.x * 255.0f),
                                     static_cast<BYTE>(value.y * 255.0f),
                                     static_cast<BYTE>(value.z * 255.0f),
                                     static_cast<BYTE>(value.w * 255.0f)};
                FreeImage_SetPixelColor(bitmap, index.x, index.y, &color);
                break;
            }
            default:
                fail();
        }
    }

    const void* Texture::get_bits() const noexcept
    {
        return FreeImage_GetBits(bitmap);
    }

    void Texture::set_filter_mode(FilterMode value) noexcept
    {
        filter_mode = value;
    }

    FilterMode Texture::get_filter_mode() const noexcept
    {
        return filter_mode;
    }

    void Texture::set_wrap_mode(WrapMode value) noexcept
    {
        wrap_mode = value;
    }

    WrapMode Texture::get_wrap_mode() const noexcept
    {
        return wrap_mode;
    }

    GLenum glinternalformat(ColorMode color, DataType data) noexcept
    {
        switch (data)
        {
        case DataType::INT8:
            switch (color)
            {
            case ColorMode::R:
                return GL_R8I;
            case ColorMode::RG:
                return GL_RG8I;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB8I;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA8I;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA8I;
            }
        case DataType::UINT8:
            switch (color)
            {
            case ColorMode::R:
                return GL_RED;
            case ColorMode::RG:
                return GL_RG;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA;
            }
        case DataType::INT16:
            switch (color)
            {
            case ColorMode::R:
                return GL_R16I;
            case ColorMode::RG:
                return GL_RG16I;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB16I;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA16I;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA16I;
            }
        case DataType::UINT16:
            switch (color)
            {
            case ColorMode::R:
                return GL_R16UI;
            case ColorMode::RG:
                return GL_RG16UI;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB16UI;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA16UI;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA16UI;
            }
        case DataType::INT32:
            switch (color)
            {
            case ColorMode::R:
                return GL_R32I;
            case ColorMode::RG:
                return GL_RG32I;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB32I;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA32I;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA32I;
            }
        case DataType::UINT32:
            switch (color)
            {
            case ColorMode::R:
                return GL_R32UI;
            case ColorMode::RG:
                return GL_RG32UI;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB32UI;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA32UI;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA32UI;
            }
        case DataType::FLOAT:
        case DataType::DOUBLE:
            switch (color)
            {
            case ColorMode::R:
                return GL_R32F;
            case ColorMode::RG:
                return GL_RG32F;
            case ColorMode::RGB:
            case ColorMode::BGR:
                return GL_RGB32F;
            case ColorMode::RGBA:
            case ColorMode::BGRA:
                return GL_RGBA32F;
            default:
                fail("Unexpected color mode.");
                return GL_RGBA32F;
            }
        default:
            fail("Unexpected type.");
            return GL_RGB;
        }
    }

    GLenum glformat(ColorMode color) noexcept
    {
        switch (color)
        {
        case ColorMode::R:
            return GL_RED;
        case ColorMode::RG:
            return GL_RG;
        case ColorMode::RGB:
            return GL_RGB;
        case ColorMode::BGR:
            return GL_BGR;
        case ColorMode::RGBA:
            return GL_RGBA;
        case ColorMode::BGRA:
            return GL_BGRA;
        default:
            fail("Unexpected color mode.");
            return GL_RGB;
        }
    }

    GLenum gltype(DataType data) noexcept
    {
        switch (data)
        {
        case DataType::INT8:
            return GL_BYTE;
        case DataType::UINT8:
            return GL_UNSIGNED_BYTE;
        case DataType::INT16:
            return GL_SHORT;
        case DataType::UINT16:
            return GL_UNSIGNED_SHORT;
        case DataType::INT32:
            return GL_INT;
        case DataType::UINT32:
            return GL_UNSIGNED_INT;
        case DataType::FLOAT:
            return GL_FLOAT;
        case DataType::DOUBLE:
            return GL_DOUBLE;
        default:
            fail("Unexpected type.");
            return GL_RGB;
        }
    }

    void Texture::upload()
    {
        glGenTextures(1, &glid);
        glBindTexture(GL_TEXTURE_2D, glid);
        glObjectLabel(GL_TEXTURE, glid, static_cast<GLsizei>(label.size()), label.data());

        switch (filter_mode)
        {
        case FilterMode::LINEAR:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            break;
        case FilterMode::NEAREST:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            break;
        default:
            fail("Unknown filter mode.");
            break;
        }

        switch (wrap_mode)
        {
        case WrapMode::CLAMP:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case WrapMode::REPEAT:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        default:
            fail("Unknown wrap mode.");
            break;
        }

        auto size              = get_size();
        auto gl_internalformat = glinternalformat(get_color_mode(), get_data_type());
        auto gl_format         = glformat(get_color_mode());
        auto gl_type           = gltype(get_data_type());
        glTexImage2D(GL_TEXTURE_2D, 0, gl_internalformat, size.x, size.y, 0, gl_format, gl_type, get_bits());

        check_glerror();
    }

    void Texture::release()
    {
        if (glid != 0)
        {
            glDeleteTextures(1, &glid);
            glid = 0;
        }
    }

    bool Texture::is_uploaded() const noexcept
    {
        return glid != 0;
    }

    void Texture::bind(glm::uint slot)
    {
        if (!is_uploaded())
        {
            upload();
        }

        check(glid != 0);
        glBindTexture(GL_TEXTURE_2D, glid);
        check_glerror();
    }

    FREE_IMAGE_FORMAT get_file_type(const std::filesystem::path& file)
    {
        switch (hash(tolower(file.extension().string())))
        {
        case hash(".png"):
            return FIF_PNG;
        case hash(".jpeg"):
        case hash(".jpg"):
            return FIF_JPEG;
        case hash(".bmp"):
            return FIF_BMP;
        case hash(".gif"):
            return FIF_GIF;
        case hash(".webp"):
            return FIF_WEBP;
        default:
            return FIF_UNKNOWN;
        }
    }

    void Texture::save(const std::filesystem::path& file) const
    {
        check(bitmap);
        std::filesystem::create_directories(file.parent_path());
        auto fif = get_file_type(file);
        #ifdef _WIN32
        auto r = FreeImage_SaveU(fif, bitmap, file.c_str(), 0);
        #else
        auto r = FreeImage_Save(fif, bitmap, file.c_str(), 0);
        #endif
        if (r == FALSE)
        {
            throw std::runtime_error(std::format("Failed to save {}.", file.string()));
        }
    }

    size_t Texture::get_hash() const noexcept
    {
        auto mem_size = FreeImage_GetMemorySize(bitmap);
        auto data     = FreeImage_GetBits(bitmap);

        return hash(
            rex::array_view<BYTE>(data, mem_size),
            filter_mode,
            wrap_mode
        );
    }

    float compare(const std::shared_ptr<Texture>& a, const std::shared_ptr<Texture>& b)
    {
        if (a == nullptr)
        {
            throw std::runtime_error("compare: a is null");
        }
        if (b == nullptr)
        {
            throw std::runtime_error("compare: b is null");
        }

        if (a->get_size() != b->get_size())
        {
            throw std::runtime_error("compare: textures are not the same size");
        }

        float error = 0.0f;

        auto s = a->get_size();
        for (auto u = 0u; u < s.x; u++)
        {
            for (auto v = 0u; v < s.y; v++)
            {
                auto ac = a->get_texel({u, v});
                auto bc = b->get_texel({u, v});
                error += glm::length(glm::abs(ac - bc));
            }
        }

        return error;
    }

    std::shared_ptr<Texture> diff(const std::shared_ptr<Texture>& a, const std::shared_ptr<Texture>& b)
    {
        if (a == nullptr)
        {
            throw std::runtime_error("diff: a is null");
        }
        if (b == nullptr)
        {
            throw std::runtime_error("diff: b is null");
        }
        if (a->get_size() != b->get_size())
        {
            throw std::runtime_error("diff: textures are not the same size");
        }

        auto s = a->get_size();
        auto result = std::make_shared<Texture>(s, ColorMode::RGBA, DataType::UINT8, nullptr, "diff");
        for (auto u = 0u; u < s.x; u++)
        {
            for (auto v = 0u; v < s.y; v++)
            {
                auto ac = a->get_texel({u, v});
                auto bc = b->get_texel({u, v});
                auto diff = glm::abs(ac - bc);
                diff.a = 1.0f - diff.a;
                result->set_texel({u, v}, diff);
            }
        }
        return result;
    }
}
