//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"
#include "Texture.h"

#include <SDL2/SDL_image.h>
#include <FreeImage.h>

#include "utils.h"

namespace pkzo
{
    class GraphicTextureImpl
    {
    public:
        virtual ~GraphicTextureImpl() = default;

        virtual bool is_uploaded() const noexcept = 0;
        virtual void upload(const glm::uvec2& size, ColorMode mode, DataType type, const void* memory) noexcept = 0;
        virtual void bind(glm::uint slot) noexcept = 0;
    };

    class OpenGLTextureImpl : public GraphicTextureImpl
    {
    public:
        OpenGLTextureImpl(const std::string& label);
        ~OpenGLTextureImpl();

        bool is_uploaded() const noexcept override;
        void upload(const glm::uvec2& size, ColorMode mode, DataType type, const void* memory) noexcept override;
        void bind(glm::uint slot) noexcept override;

    private:
        std::string label;
        glm::uint   gl_id = 0u;
    };

    OpenGLTextureImpl::OpenGLTextureImpl(const std::string& l)
    : label(l) {}

    OpenGLTextureImpl::~OpenGLTextureImpl()
    {
        if (gl_id)
        {
            glDeleteTextures(1, &gl_id);
            gl_id = 0;
            DBG_ASSERT(glGetError() == GL_NO_ERROR);
        }
    }

    bool OpenGLTextureImpl::is_uploaded() const noexcept
    {
        return gl_id != 0;
    }

    GLenum glmode(ColorMode mode) noexcept
    {
        switch (mode)
        {
            case ColorMode::R:
                return GL_R;
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
                DBG_FAIL("Unexpected color mode.");
                return GL_RGB;
        }
    }

    GLenum gltype(DataType type) noexcept
    {
        switch (type)
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
            DBG_FAIL("Unexpected type.");
            return GL_RGB;
        }
    }

    void OpenGLTextureImpl::upload(const glm::uvec2& size, ColorMode mode, DataType type, const void* memory) noexcept
    {
        DBG_ASSERT(gl_id == 0);

        glGenTextures(1, &gl_id);
        glBindTexture(GL_TEXTURE_2D, gl_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        GLenum gl_mode = glmode(mode);
        GLenum gl_type = gltype(type);
        // USE RGBA_32F and similar
        DBG_ASSERT(type == DataType::FLOAT || type == DataType::DOUBLE);

        glTexImage2D(GL_TEXTURE_2D, 0, gl_mode, size.x, size.y, 0, gl_mode, gl_type, memory);
        DBG_ASSERT(glGetError() == GL_NO_ERROR);

    #ifndef NDEBUG
        glObjectLabel(GL_TEXTURE, gl_id, 0, label.data());
        DBG_ASSERT(glGetError() == GL_NO_ERROR);
    #endif
    }

    void OpenGLTextureImpl::bind(glm::uint slot) noexcept
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, gl_id);
        DBG_ASSERT(glGetError() == GL_NO_ERROR);
    }

    class TextureImpl
    {
    public:
        virtual ~TextureImpl() = default;

        virtual glm::uvec2 get_size() const noexcept = 0;
        virtual ColorMode get_color_mode() const noexcept = 0;
        virtual DataType get_data_type() const noexcept = 0;
        virtual glm::vec4 get_texel(const glm::uvec2& index) const noexcept = 0;
        virtual void* get_data() const noexcept = 0;
        virtual void save(const std::filesystem::path& file) const = 0;
    };

    class SdlTextureImpl : public TextureImpl
    {
    public:
        SdlTextureImpl(SDL_Surface* surface) noexcept;
        ~SdlTextureImpl();

        glm::uvec2 get_size() const noexcept override;
        ColorMode get_color_mode() const noexcept override;
        DataType get_data_type() const noexcept override;
        glm::vec4 get_texel(const glm::uvec2& index) const noexcept override;
        void* get_data() const noexcept override;
        void save(const std::filesystem::path& file) const override;

    public:
        SdlSentry    sdl_sentry;
        SDL_Surface* surface = nullptr;
    };

    SdlTextureImpl::SdlTextureImpl(SDL_Surface* s) noexcept
    : surface(s)
    {
        DBG_ASSERT(surface != nullptr);
    }

    SdlTextureImpl::~SdlTextureImpl()
    {
        DBG_ASSERT(surface != nullptr);
        SDL_FreeSurface(surface);
    }

    glm::uvec2 SdlTextureImpl::get_size() const noexcept
    {
        DBG_ASSERT(surface != nullptr);
        return {surface->w, surface->h};
    }

    ColorMode SdlTextureImpl::get_color_mode() const noexcept
    {
        DBG_ASSERT(surface != nullptr);
        switch (surface->format->BytesPerPixel)
        {
        case 1:
            return ColorMode::R;
        case 2:
            return ColorMode::RG;
        case 3:
            return ColorMode::RGB;
        case 4:
            return ColorMode::RGBA;
        default:
            DBG_FAIL("Unexpected bytes per pixel.");
            return ColorMode::UNKNOWN;
        }
    }

    DataType SdlTextureImpl::get_data_type() const noexcept
    {
        return DataType::UINT8;
    }

    Uint32 getpixel(SDL_Surface *surface, int x, int y)
    {
        int bpp = surface->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to retrieve */
        Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

        switch (bpp)
        {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
        }
    }

    glm::vec4 SdlTextureImpl::get_texel(const glm::uvec2& index) const noexcept
    {
        Uint8 r, g, b, a;
        Uint32 data = getpixel(surface, index.x, index.y);
        SDL_GetRGBA(data, surface->format, &r, &g, &b, &a);
        return {static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f, static_cast<float>(a) / 255.0f};
    }

    void* SdlTextureImpl::get_data() const noexcept
    {
        DBG_ASSERT(surface != nullptr);
        return surface->pixels;
    }

    auto bytes2mode(uint8_t bytes)
    {
        switch (bytes)
        {
        case 1:
            return ColorMode::R;
        case 2:
            return ColorMode::RG;
        case 3:
            return ColorMode::RGB;
        case 4:
            return ColorMode::RGBA;
        default:
            DBG_ASSERT(false);
            return ColorMode::UNKNOWN;
        }
    }

    void SdlTextureImpl::save(const std::filesystem::path& file) const
    {
        DBG_FAIL("TODO");
        // TODO
    }

    class FreeImageTextureImpl : public TextureImpl
    {
    public:
        FreeImageTextureImpl(const std::filesystem::path& file);
        FreeImageTextureImpl(const glm::uvec2& size, ColorMode mode, DataType type, const void* memory);
        ~FreeImageTextureImpl();

        glm::uvec2 get_size() const noexcept override;
        ColorMode get_color_mode() const noexcept override;
        DataType get_data_type() const noexcept override;
        glm::vec4 get_texel(const glm::uvec2& index) const noexcept override;
        void* get_data() const noexcept override;
        void save(const std::filesystem::path& file) const override;

    public:
        FIBITMAP* bitmap;
    };

    FreeImageTextureImpl::FreeImageTextureImpl(const std::filesystem::path& file)
    {
    #ifdef _WIN32
        auto fif = FreeImage_GetFileTypeU(file.c_str(), 0);
        bitmap = FreeImage_LoadU(fif, file.c_str(), JPEG_ACCURATE);
    #else
        auto fif = FreeImage_GetFileType(file.c_str(), 0);
        bitmap = FreeImage_Load(fif, file.c_str(), JPEG_ACCURATE);
    #endif
        if (bitmap == nullptr)
        {
            throw std::runtime_error("Failed to load " + file.u8string());
        }
    }

    auto get_bpp(ColorMode mode, DataType type)
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
            DBG_ASSERT(false);
        }

        switch (type)
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
            DBG_ASSERT(false);
            return 0u;
        }
    }

    FREE_IMAGE_TYPE fi_type(DataType type)
    {
        switch (type)
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

    FreeImageTextureImpl::FreeImageTextureImpl(const glm::uvec2& size, ColorMode mode, DataType type, const void* memory)
    {
        auto raw = reinterpret_cast<BYTE*>(const_cast<void*>(memory));
        auto fitype = fi_type(type);
        auto bpp = get_bpp(mode, type);
        auto Bpp = bpp / 8u;
        auto rm = red_mask(mode);
        auto gm = green_mask(mode);
        auto bm = blue_mask(mode);
        bitmap = FreeImage_ConvertFromRawBitsEx(TRUE, raw, fitype, size.x, size.y, Bpp * size.x, bpp, rm, gm, bm);
        if (bitmap == nullptr)
        {
            throw std::runtime_error("Failed to convert raw data.");
        }
    }

    FreeImageTextureImpl::~FreeImageTextureImpl()
    {
        DBG_ASSERT(bitmap != nullptr);
        FreeImage_Unload(bitmap);
    }

    glm::uvec2 FreeImageTextureImpl::get_size() const noexcept
    {
        DBG_ASSERT(bitmap != nullptr);
        return {FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap)};
    }

    glm::vec4 FreeImageTextureImpl::get_texel(const glm::uvec2& index) const noexcept
    {
        RGBQUAD color;
        FreeImage_GetPixelColor(bitmap, index.x, index.y, &color);
        return {color.rgbRed/255.0f, color.rgbGreen/255.0f, color.rgbBlue/255.0f, color.rgbReserved/255.0f};
    }

    ColorMode FreeImageTextureImpl::get_color_mode() const noexcept
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

    DataType FreeImageTextureImpl::get_data_type() const noexcept
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

    void* FreeImageTextureImpl::get_data() const noexcept
    {
        return FreeImage_GetBits(bitmap);
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
        switch (hash(tolower(file.extension().u8string())))
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

    void FreeImageTextureImpl::save(const std::filesystem::path& file) const
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
            throw std::runtime_error("Failed to save " + file.u8string());
        }
    }

    Texture::Texture(const std::filesystem::path& file)
    : impl(std::make_unique<FreeImageTextureImpl>(file)), graphic_impl(std::make_unique<OpenGLTextureImpl>(file.filename().u8string())) {}

    Texture::Texture(const glm::uvec2& size, ColorMode mode, DataType type, const void* memory, const std::string& label)
    : impl(std::make_unique<FreeImageTextureImpl>(size, mode, type, memory)), graphic_impl(std::make_unique<OpenGLTextureImpl>(label)) {}

    Texture::Texture(SDL_Surface* surface, const std::string& label) noexcept
    : impl(std::make_unique<SdlTextureImpl>(surface)), graphic_impl(std::make_unique<OpenGLTextureImpl>(label)) {}

    Texture::~Texture() = default;

    glm::uvec2 Texture::get_size() const noexcept
    {
        DBG_ASSERT(impl);
        return impl->get_size();
    }

    ColorMode Texture::get_color_mode() const noexcept
    {
        DBG_ASSERT(impl);
        return impl->get_color_mode();
    }

    DataType Texture::get_data_type() const noexcept
    {
        DBG_ASSERT(impl);
        return impl->get_data_type();
    }

    glm::vec4 Texture::get_texel(const glm::uvec2& index) const noexcept
    {
        DBG_ASSERT(impl);
        return impl->get_texel(index);
    }

    void* Texture::get_data() const noexcept
    {
        DBG_ASSERT(impl);
        return impl->get_data();
    }

    void Texture::upload() noexcept
    {
        DBG_ASSERT(impl);
        DBG_ASSERT(graphic_impl);
        graphic_impl->upload(impl->get_size(), impl->get_color_mode(), impl->get_data_type(), impl->get_data());
    }

    void Texture::bind(glm::uint slot) noexcept
    {
        DBG_ASSERT(graphic_impl);
        return graphic_impl->bind(slot);
    }

    void Texture::save(const std::filesystem::path& file)
    {
        DBG_ASSERT(impl);
        return impl->save(file);
    }
}
