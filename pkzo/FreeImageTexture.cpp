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

#include "pch.h"

#include "FreeImageTexture.h"

#include <iostream>

#include <tinyformat.h>

#include "debug.h"

namespace pkzo
{
    void free_image_trace(FREE_IMAGE_FORMAT, const char *message)
    {
        trace(message);
    }

    std::atomic<unsigned int> FreeImageSentry::use_count = 0;

    FreeImageSentry::FreeImageSentry()
    {
        if (use_count.fetch_add(1u) == 0u)
        {
            FreeImage_Initialise();
            FreeImage_SetOutputMessage(free_image_trace);
        }
    }

    FreeImageSentry::~FreeImageSentry()
    {
        if (use_count.fetch_sub(1u) == 1u)
        {
            FreeImage_DeInitialise();
        }
    }

    FreeImageTexture::FreeImageTexture(const FileLoadSpecs& specs)
    : id(specs.file.filename().string()), filter(specs.filter), clamp(specs.clamp)
    {
        #ifdef _WIN32
        auto fif = FreeImage_GetFileTypeU(specs.file.c_str(), 0);
        bitmap = FreeImage_LoadU(fif, specs.file.c_str(), JPEG_ACCURATE);
        #else
        auto fif = FreeImage_GetFileType(specs.file.c_str(), 0);
        bitmap = FreeImage_Load(fif, specs.file.c_str(), JPEG_ACCURATE);
        #endif
        if (bitmap == nullptr)
        {
            throw std::runtime_error(tfm::format("Failed to load '%s'.", specs.file));
        }
    }

    FreeImageTexture::FreeImageTexture(const MemorLoadSpecs& specs)
    : id(specs.id), filter(specs.filter), clamp(specs.clamp)
    {
        auto stream = FreeImage_OpenMemory(reinterpret_cast<BYTE*>(const_cast<void*>(specs.memory)), static_cast<DWORD>(specs.size));
        bitmap = FreeImage_LoadFromMemory(static_cast<FREE_IMAGE_FORMAT>(specs.format), stream, JPEG_ACCURATE);
        FreeImage_CloseMemory(stream);

        if (bitmap == nullptr)
        {
            throw std::runtime_error("Failed to load memory");
        }
    }

    unsigned int get_bpp(ColorMode mode, DataType type)
    {
        using enum ColorMode;
        using enum DataType;

        auto components = 0u;
        switch (mode)
        {
            case MONO:
                components = 1u;
                break;
            case RGB:
            case BGR:
                components = 3u;
                break;
            case RGBA:
            case BGRA:
                components = 4u;
                break;
            default:
                std::unreachable();
        }

        switch (type)
        {
            case UNSIGNED_BYTE:
                return 8u * components;
            case FLOAT:
                return 32u * components;
            default:
                std::unreachable();
        }
    }

    FREE_IMAGE_TYPE fi_type(ColorMode mode, DataType type)
    {
        using enum DataType;
        using enum ColorMode;

        switch (type)
        {
            case UNSIGNED_BYTE:
                return FIT_BITMAP;
            case FLOAT:
                switch (mode)
                {
                    case MONO:
                        return FIT_FLOAT;
                    case RGB:
                        return FIT_RGBF;
                        break;
                    case RGBA:
                        return FIT_RGBAF;
                    case BGR:
                    case BGRA:
                        throw std::runtime_error("BGR & BGRA textures not supported with floats.");
                    default:
                        std::unreachable();
                }

            default:
                std::unreachable();
        }
    }

    unsigned int red_mask(ColorMode mode)
    {
        using enum ColorMode;

        switch (mode)
        {
            case MONO:
            case RGB:
            case RGBA:
                return 0x0000FF;
            case BGR:
            case BGRA:
                return 0xFF0000;
            default:
                std::unreachable();
        }
    }

    unsigned int green_mask(ColorMode mode)
    {
        using enum ColorMode;

        switch (mode)
        {
            case MONO:
                return 0x00;
            case RGB:
            case RGBA:
            case BGR:
            case BGRA:
                return 0x00FF00;
            default:
                std::unreachable();
        }
    }

    unsigned int blue_mask(ColorMode mode)
    {
        using enum ColorMode;

        switch (mode)
        {
            case MONO:
                return 0x00;
            case RGB:
            case RGBA:
                return 0xFF0000;
            case BGR:
            case BGRA:
                return 0x0000FF;
            default:
                std::unreachable();
        }
    }

    FreeImageTexture::FreeImageTexture(const CreateSpecs& specs)
    : id(specs.id), filter(specs.filter), clamp(specs.clamp)
    {
        auto raw    = reinterpret_cast<BYTE*>(const_cast<void*>(specs.memory));
        auto fitype = fi_type(specs.color_mode, specs.data_type);
        auto bpp    = get_bpp(specs.color_mode, specs.data_type);
        auto Bpp    = bpp / 8u;
        auto rm     = red_mask(specs.color_mode);
        auto gm     = green_mask(specs.color_mode);
        auto bm     = blue_mask(specs.color_mode);
        if (raw != nullptr)
        {
            bitmap = FreeImage_ConvertFromRawBitsEx(TRUE, raw, fitype, specs.size.x, specs.size.y, Bpp * specs.size.x, bpp, rm, gm, bm);
            if (bitmap == nullptr)
            {
                throw std::runtime_error("Failed to convert raw image data.");
            }
        }
        else
        {
            bitmap = FreeImage_AllocateT(fitype, specs.size.x, specs.size.y, bpp, rm, gm, bm);
            if (bitmap == nullptr)
            {
                throw std::runtime_error("Failed to allocate image.");
            }
        }
    }

    FreeImageTexture::~FreeImageTexture()
    {
        check(bitmap != nullptr);
        FreeImage_Unload(bitmap);
        bitmap = nullptr;
    }

    const std::string& FreeImageTexture::get_id() const
    {
        return id;
    }

    glm::uvec2 FreeImageTexture::get_size() const
    {
        check(bitmap != nullptr);
        return glm::uvec2(FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap));
    }

    ColorMode FreeImageTexture::get_color_mode() const
    {
        check(bitmap != nullptr);
        switch (FreeImage_GetImageType(bitmap))
        {
            case FIT_BITMAP:
                switch (FreeImage_GetBPP(bitmap))
                {
                    case 8:
                        return ColorMode::MONO;
                    case 24:
                        return ColorMode::BGR;
                    case 32:
                        return ColorMode::BGRA;
                }
            case FIT_FLOAT:
                return ColorMode::MONO;
            case FIT_RGBF:
                return ColorMode::RGB;
            case FIT_RGBAF:
                return ColorMode::RGBA;
        }

        throw std::runtime_error("Texture::get_color_mode: unexpected type");
    }

    DataType FreeImageTexture::get_data_type() const
    {
        check(bitmap != nullptr);
        switch (FreeImage_GetImageType(bitmap))
        {
            case FIT_BITMAP:
                return DataType::UNSIGNED_BYTE;
            case FIT_FLOAT:
            case FIT_RGBF:
            case FIT_RGBAF:
                return DataType::FLOAT;
        }

        throw std::runtime_error("Texture::get_data_type: unexpected type");
    }

    const void* FreeImageTexture::get_memory() const
    {
        check(bitmap != nullptr);
        return FreeImage_GetBits(bitmap);
    }

    TextureFilter FreeImageTexture::get_filter() const
    {
        return filter;
    }

    Clamp FreeImageTexture::get_clamp() const
    {
        return clamp;
    }

    std::shared_ptr<MemoryTexture> FreeImageTexture::download()
    {
        return shared_from_this();
    }

    glm::vec4 FreeImageTexture::get_pixel(const glm::uvec2& pos) const
    {
        check(bitmap != nullptr);
        check(FreeImage_GetImageType(bitmap) == FIT_BITMAP);
        auto color = RGBQUAD{};
        FreeImage_GetPixelColor(bitmap, pos.x, pos.y, &color);
        return glm::vec4(color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved) / 255.0f;
    }

    void FreeImageTexture::set_pixel(const glm::uvec2& pos, const glm::vec4& value)
    {
        check(bitmap != nullptr);
        check(FreeImage_GetImageType(bitmap) == FIT_BITMAP);

        RGBQUAD color;
        color.rgbRed      = static_cast<BYTE>(value.r * 255.0f);
        color.rgbGreen    = static_cast<BYTE>(value.g * 255.0f);
        color.rgbBlue     = static_cast<BYTE>(value.b * 255.0f);
        color.rgbReserved = static_cast<BYTE>(value.a * 255.0f);
        FreeImage_SetPixelColor(bitmap, pos.x, pos.y, &color);
    }

    void FreeImageTexture::save(const std::filesystem::path& file) const
    {
        check(bitmap != nullptr);

        std::filesystem::create_directories(file.parent_path());

        #ifdef _WIN32
        auto fif = FreeImage_GetFIFFromFilenameU(file.c_str());
        FreeImage_SaveU(fif, bitmap, file.c_str());
        #else
        auto fif = FreeImage_GetFIFFromFilename(file.c_str());
        FreeImage_Save(fif, bitmap, file.c_str());
        #endif
    }
}
