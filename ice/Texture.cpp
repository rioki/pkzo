// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
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
#include "Texture.h"

#include "utils.h"

namespace ice
{
    void free_image_trace(FREE_IMAGE_FORMAT fif, const char* message)
    {
        trace(message);
    }

    Texture::Texture(const std::filesystem::path& _file)
    : label(_file.filename().string()), file(_file)
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
            throw std::runtime_error(std::format("Failed to load {}", file.string()));
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
            assert(false);
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
            assert(false);
            return 0u;
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
            assert(false);
            return FIT_UNKNOWN;
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
            assert(false);
            return 0;
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
            assert(false);
            return 0;
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
            assert(false);
            return 0;
        }
    }

    Texture::Texture(const glm::uvec2& size, ColorMode mode, DataType group, const void* memory, const std::string& _label)
    : label(_label)
    {
        auto raw = reinterpret_cast<BYTE*>(const_cast<void*>(memory));
        auto fitype = fi_type(group);
        auto bpp = get_bpp(mode, group);
        auto Bpp = bpp / 8u;
        auto rm = red_mask(mode);
        auto gm = green_mask(mode);
        auto bm = blue_mask(mode);
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

    Texture::~Texture()
    {
        // bitmap may be null after move
        assert(bitmap != nullptr);
        FreeImage_Unload(bitmap);
    }

    const std::filesystem::path& Texture::get_file() const noexcept
    {
        return file;
    }

    glm::uvec2 Texture::get_size() const noexcept
    {
        assert(bitmap != nullptr);
        return {FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap)};
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
        assert(bitmap != nullptr);

        auto type = FreeImage_GetImageType(bitmap);
        switch (type)
        {
            case FIT_UNKNOWN:
                assert(false);
                return glm::vec4(0.0f);
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
                assert(false);
                return glm::vec4(0.0f);
        }

    }

    void Texture::set_texel(const glm::uvec2& index, const glm::vec4& value) noexcept
    {
        increment_version();
        auto type = FreeImage_GetImageType(bitmap);
        switch (type)
        {
            case FIT_UNKNOWN:
                assert(false);
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
                assert(false);
                break;
        }
    }

    ColorMode Texture::get_color_mode() const noexcept
    {
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
                assert(false);
                return ColorMode::UNKNOWN;
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
            assert(false);
            return ColorMode::UNKNOWN;
        }
    }

    DataType Texture::get_data_type() const noexcept
    {
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
            assert(false);
            return DataType::UNKNOWN;
        }
    }

    void* Texture::get_data() const noexcept
    {
        return FreeImage_GetBits(bitmap);
    }

    void Texture::set_filter_mode(FilterMode value) noexcept
    {
        increment_version();
        filter_mode = value;
    }

    FilterMode Texture::get_filter_mode() const noexcept
    {
        return filter_mode;
    }

    void Texture::set_wrap_mode(WrapMode value) noexcept
    {
        increment_version();
        wrap_mode = value;
    }

    WrapMode Texture::get_wrap_mode() const noexcept
    {
        return wrap_mode;
    }

    const std::string& Texture::get_label() const noexcept
    {
        return label;
    }


    std::string tolower(const std::string& str, const std::locale& loc = std::locale("C"))
    {
        std::string result(str.size(), '\0');

        std::transform(str.begin(), str.end(), result.begin(), [&] (char c) {
            return std::tolower(c, loc);
        });

        return result;
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
        std::filesystem::create_directories(file.parent_path());
        auto fif = get_file_type(file);
    #ifdef _WIN32
        auto r = FreeImage_SaveU(fif, bitmap, file.c_str(), 0);
    #else
        auto r = FreeImage_Save(fif, bitmap, file.c_str(), 0);
    #endif
        if (r == FALSE)
        {
            throw std::runtime_error(std::format("Failed to save {}", file.string()));
        }
    }

    float compare(const std::shared_ptr<Texture>& a, const std::shared_ptr<Texture>& b)
    {
        if (a == nullptr)
        {
            throw std::invalid_argument("compare: left texture is null");
        }

        if (b == nullptr)
        {
            throw std::invalid_argument("compare: right texture is null");
        }

        if (a->get_size() != b->get_size())
        {
            throw std::invalid_argument("compare: textures are not the same size");
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
            throw std::invalid_argument("diff: left texture is null");
        }

        if (b == nullptr)
        {
            throw std::invalid_argument("diff: right texture is null");
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

    std::shared_ptr<Texture> make_black_texture()
    {
        static unsigned char buffer[4] = {0u, 0u, 0u, 255u};
        return std::make_shared<Texture>(glm::uvec2(1), ice::ColorMode::RGBA, ice::DataType::UINT8, buffer, "black");
    }

    std::shared_ptr<Texture> make_white_texture()
    {
        static unsigned char buffer[4] = {255u, 255u, 255u, 255u};
        return std::make_shared<Texture>(glm::uvec2(1), ice::ColorMode::RGBA, ice::DataType::UINT8, buffer, "white");
    }

    std::shared_ptr<Texture> make_normal_texture()
    {
        static unsigned char buffer[4] = {127u, 127u, 255u, 255u};
        return std::make_shared<Texture>(glm::uvec2(1), ice::ColorMode::RGBA, ice::DataType::UINT8, buffer, "normal");
    }
}
