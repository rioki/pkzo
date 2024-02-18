// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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
#include "Image.h"

#include <freeimage.h>

namespace pkzo
{
    void free_image_trace(FREE_IMAGE_FORMAT fif, const char *message)
    {
        trace(message);
    }

    Image::Image(const std::filesystem::path& f)
    : file(f)
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
            throw std::runtime_error(tfm::format("Failed to load '%s'.", file));
        }
    }

    uint32_t get_bpp(ColorMode mode)
    {
        switch (mode)
        {
        case ColorMode::RGB:
        case ColorMode::BGR:
            return 3u;
            break;
        case ColorMode::RGBA:
        case ColorMode::BGRA:
            return 4u;
            break;
        default:
            assert(false);
            return 0u;
        }
    }

    uint32_t red_mask(ColorMode mode)
    {
        switch (mode)
        {
        case ColorMode::RGB:
        case ColorMode::RGBA:
            return 0xFF0000;
        case ColorMode::BGR:
        case ColorMode::BGRA:
            return 0x0000FF;
        default:
            assert(false);
            return 0x00;
        }
    }

    uint32_t green_mask(ColorMode mode)
    {
        switch (mode)
        {
        case ColorMode::RGB:
        case ColorMode::RGBA:
        case ColorMode::BGR:
        case ColorMode::BGRA:
            return 0x00FF00;
        default:
            assert(false);
            return 0x00;
        }
    }

    uint32_t blue_mask(ColorMode mode)
    {
        switch (mode)
        {
        case ColorMode::RGB:
        case ColorMode::RGBA:
            return 0x0000FF;
        case ColorMode::BGR:
        case ColorMode::BGRA:
            return 0xFF0000;
        default:
            assert(false);
            return 0x00;
        }
    }

    Image::Image(glm::uvec2 size, ColorMode mode, const uint8_t* memory)
    {
        auto raw    = const_cast<BYTE*>(reinterpret_cast<const BYTE*>(memory));
        auto fitype = FIT_BITMAP;
        auto Bpp    = get_bpp(mode);
        auto bpp    = Bpp * 8u;
        auto rm     = red_mask(mode);
        auto gm     = green_mask(mode);
        auto bm     = blue_mask(mode);
        if (memory != nullptr)
        {
            bitmap = FreeImage_ConvertFromRawBitsEx(TRUE, raw, fitype, size.x, size.y, Bpp * size.x, bpp, rm, gm, bm);
            if (bitmap == nullptr)
            {
                throw std::runtime_error("Failed to convert raw image data.");
            }
        }
        else
        {
            bitmap = FreeImage_AllocateT(fitype, size.x, size.y, bpp, rm, gm, bm);
            if (bitmap == nullptr)
            {
                throw std::runtime_error("Failed to allocate image.");
            }
        }
    }

    Image::~Image()
    {
        if (bitmap != nullptr)
        {
            FreeImage_Unload(bitmap);
        }
    }

    Image::Image(Image&& other) noexcept
    {
        std::swap(bitmap, other.bitmap);
    }

    Image& Image::operator = (Image&& other) noexcept
    {
        std::swap(bitmap, other.bitmap);
        return *this;
    }

    const std::filesystem::path& Image::get_file() const noexcept
    {
        return file;
    }

    glm::uvec2 Image::get_size() const noexcept
    {
        return glm::uvec2(FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap));
    }

    ColorMode Image::get_color_mode() const noexcept
    {
        auto bpp = FreeImage_GetBPP(bitmap);
        switch (bpp)
        {
            case 24:
                return ColorMode::BGR;
            case 32:
                return ColorMode::BGRA;
            default:
                fail();
        }
    }
    const uint8_t* Image::get_data() const noexcept
    {
        assert(bitmap != nullptr);
        return FreeImage_GetBits(bitmap);
    }

    glm::vec4 Image::get_pixel(glm::uvec2 pos) const noexcept
    {
        assert(bitmap != nullptr);
        assert(FreeImage_GetImageType(bitmap) == FIT_BITMAP);
        auto color = RGBQUAD{};
        FreeImage_GetPixelColor(bitmap, pos.x, pos.y, &color);
        return glm::vec4(color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved) / 255.0f;
    }

    void Image::set_pixel(glm::uvec2 pos, glm::vec4 color) noexcept
    {
        assert(bitmap != nullptr);
        assert(FreeImage_GetImageType(bitmap) == FIT_BITMAP);
        auto c = RGBQUAD{
            static_cast<BYTE>(color.r * 255.0f),
            static_cast<BYTE>(color.g * 255.0f),
            static_cast<BYTE>(color.b * 255.0f),
            static_cast<BYTE>(color.a * 255.0f)
        };
        FreeImage_SetPixelColor(bitmap, pos.x, pos.y, &c);
    }

    void Image::save(const std::filesystem::path& file) const
    {
        assert(bitmap != nullptr);
        #ifdef _WIN32
        auto fif = FreeImage_GetFIFFromFilenameU(file.c_str());
        FreeImage_SaveU(fif, bitmap, file.c_str());
        #else
        auto fif = FreeImage_GetFIFFromFilename(file.c_str());
        FreeImage_Save(fif, bitmap, file.c_str());
        #endif
    }

    float compare(const Image& a, const Image& b)
    {

        if (a.get_size() != b.get_size())
        {
            throw std::runtime_error("compare: textures are not the same size");
        }

        float error = 0.0f;

        auto s = a.get_size();
        for (auto u = 0u; u < s.x; u++)
        {
            for (auto v = 0u; v < s.y; v++)
            {
                auto ac = a.get_pixel({u, v});
                auto bc = b.get_pixel({u, v});
                error += glm::length(glm::abs(ac - bc));
            }
        }

        return error;
    }

    Image diff(const Image& a, const Image& b)
    {
        if (a.get_size() != b.get_size())
        {
            throw std::runtime_error("diff: textures are not the same size");
        }

        auto s = a.get_size();
        auto result = Image(s, ColorMode::RGBA);
        for (auto u = 0u; u < s.x; u++)
        {
            for (auto v = 0u; v < s.y; v++)
            {
                auto ac = a.get_pixel({u, v});
                auto bc = b.get_pixel({u, v});
                auto diff = glm::abs(ac - bc);
                diff.a = 1.0f - diff.a;
                result.set_pixel({u, v}, diff);
            }
        }
        return result;
    }
}
