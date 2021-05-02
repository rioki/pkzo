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

#include <FreeImage.h>

#include "utils.h"

namespace pkzo
{
    class GraphicTextureImpl
    {
    public:
        virtual ~GraphicTextureImpl() = default;

        virtual void set_filter_mode(FilterMode value) noexcept = 0;
        virtual FilterMode get_filter_mode() const noexcept = 0;

        virtual void set_wrap_mode(WrapMode value) noexcept = 0;
        virtual WrapMode get_wrap_mode() const noexcept = 0;

        virtual bool is_uploaded() const noexcept = 0;
        virtual void upload(const glm::uvec2& size, ColorMode mode, DataType type, const void* memory) noexcept = 0;
        virtual void bind(glm::uint slot) noexcept = 0;
    };

    class OpenGLTextureImpl : public GraphicTextureImpl
    {
    public:
        OpenGLTextureImpl(const std::string& label);
        ~OpenGLTextureImpl();

        void set_filter_mode(FilterMode value) noexcept override;
        FilterMode get_filter_mode() const noexcept override;

        void set_wrap_mode(WrapMode value) noexcept override;
        WrapMode get_wrap_mode() const noexcept override;

        bool is_uploaded() const noexcept override;
        void upload(const glm::uvec2& size, ColorMode mode, DataType type, const void* memory) noexcept override;
        void bind(glm::uint slot) noexcept override;

    private:
        std::string label;
        glm::uint   gl_id       = 0u;
        FilterMode  filter_mode = FilterMode::LINEAR;
        WrapMode    wrap_mode   = WrapMode::REPEAT;
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

    void OpenGLTextureImpl::set_filter_mode(FilterMode value) noexcept
    {
        DBG_ASSERT(!is_uploaded());
        filter_mode = value;
    }

    FilterMode OpenGLTextureImpl::get_filter_mode() const noexcept
    {
        return filter_mode;
    }

    void OpenGLTextureImpl::set_wrap_mode(WrapMode value) noexcept
    {
        DBG_ASSERT(!is_uploaded());
        wrap_mode = value;
    }

    WrapMode OpenGLTextureImpl::get_wrap_mode() const noexcept
    {
        return wrap_mode;
    }

    bool OpenGLTextureImpl::is_uploaded() const noexcept
    {
        return gl_id != 0;
    }

    GLenum glinternalformat(ColorMode mode, DataType type) noexcept
    {
        switch (type)
        {
        case DataType::INT8:
            switch (mode)
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
                DBG_FAIL("Unexpected color mode.");
                return GL_RGBA8I;
            }
        case DataType::UINT8:
            switch (mode)
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
                DBG_FAIL("Unexpected color mode.");
                return GL_RGBA;
            }
        case DataType::INT16:
            switch (mode)
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
                DBG_FAIL("Unexpected color mode.");
                return GL_RGBA16I;
            }
        case DataType::UINT16:
            switch (mode)
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
                DBG_FAIL("Unexpected color mode.");
                return GL_RGBA16UI;
            }
        case DataType::INT32:
            switch (mode)
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
                DBG_FAIL("Unexpected color mode.");
                return GL_RGBA32I;
            }
        case DataType::UINT32:
            switch (mode)
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
                DBG_FAIL("Unexpected color mode.");
                return GL_RGBA32UI;
            }
        case DataType::FLOAT:
        case DataType::DOUBLE:
            switch (mode)
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
                DBG_FAIL("Unexpected color mode.");
                return GL_RGBA32F;
            }
        default:
            DBG_FAIL("Unexpected type.");
            return GL_RGB;
        }
    }

    GLenum glformat(ColorMode mode) noexcept
    {
        switch (mode)
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
                DBG_FAIL("Unknown filter mode.");
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
            DBG_FAIL("Unknown filter mode.");
            break;
        }


        GLenum gl_internalformat = glinternalformat(mode, type);
        GLenum gl_format = glformat(mode);
        GLenum gl_type = gltype(type);
        glTexImage2D(GL_TEXTURE_2D, 0, gl_internalformat, size.x, size.y, 0, gl_format, gl_type, memory);
        DBG_CHECK_GLERROR("uploading texture data");

    #ifndef NDEBUG
        glObjectLabel(GL_TEXTURE, gl_id, 0, label.data());
        DBG_CHECK_GLERROR("setting texture label");
    #endif
    }

    void OpenGLTextureImpl::bind(glm::uint slot) noexcept
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, gl_id);
        DBG_CHECK_GLERROR("binding texture");
    }

    class TextureImpl
    {
    public:
        virtual ~TextureImpl() = default;

        virtual glm::uvec2 get_size() const noexcept = 0;
        virtual ColorMode get_color_mode() const noexcept = 0;
        virtual DataType get_data_type() const noexcept = 0;
        virtual glm::vec4 get_texel(const glm::uvec2& index) const noexcept = 0;
        virtual void set_texel(const glm::uvec2& index, const glm::vec4& value) noexcept = 0;
        virtual void* get_data() const noexcept = 0;
        virtual void save(const std::filesystem::path& file) const = 0;
    };

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
        void set_texel(const glm::uvec2& index, const glm::vec4& value) noexcept override;
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

    glm::vec4 FreeImageTextureImpl::get_texel(const glm::uvec2& index) const noexcept
    {
        RGBQUAD color;
        FreeImage_GetPixelColor(bitmap, index.x, index.y, &color);
        return {color.rgbRed/255.0f, color.rgbGreen/255.0f, color.rgbBlue/255.0f, has_alpha(get_color_mode()) ? color.rgbReserved/255.0f : 1.0f};
    }

    void FreeImageTextureImpl::set_texel(const glm::uvec2& index, const glm::vec4& value) noexcept
    {
        auto color = RGBQUAD{static_cast<BYTE>(value.x * 255.0f),
                             static_cast<BYTE>(value.y * 255.0f),
                             static_cast<BYTE>(value.z * 255.0f),
                             static_cast<BYTE>(value.w * 255.0f)};
        FreeImage_SetPixelColor(bitmap, index.x, index.y, &color);
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

    Texture::Texture(Texture&& other) noexcept
    : impl(std::move(other.impl)), graphic_impl(std::move(other.graphic_impl)) {}

    Texture::~Texture() = default;

    Texture& Texture::operator = (Texture&& other) noexcept
    {
        impl         = std::move(other.impl);
        graphic_impl = std::move(other.graphic_impl);
        return *this;
    }

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

    void Texture::set_texel(const glm::uvec2& index, const glm::vec4& value) noexcept
    {
        DBG_ASSERT(impl);
        impl->set_texel(index, value);
    }

    void Texture::set_filter_mode(FilterMode value) noexcept
    {
        DBG_ASSERT(graphic_impl);
        graphic_impl->set_filter_mode(value);
    }

    FilterMode Texture::get_filter_mode() const noexcept
    {
        DBG_ASSERT(graphic_impl);
        return graphic_impl->get_filter_mode();
    }

    void Texture::set_wrap_mode(WrapMode value) noexcept
    {
        DBG_ASSERT(graphic_impl);
        graphic_impl->set_wrap_mode(value);
    }

    WrapMode Texture::get_wrap_mode() const noexcept
    {
        DBG_ASSERT(graphic_impl);
        return graphic_impl->get_wrap_mode();
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
        if (!graphic_impl->is_uploaded())
        {
            upload();
        }
        graphic_impl->bind(slot);
    }

    void Texture::save(const std::filesystem::path& file) const
    {
        DBG_ASSERT(impl);
        return impl->save(file);
    }

    PKZO_EXPORT float compare(const Texture& a, const Texture& b)
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
                auto ac = a.get_texel({u, v});
                auto bc = b.get_texel({u, v});
                error += glm::length(glm::abs(ac - bc));
            }
        }

        return error;
    }

    PKZO_EXPORT Texture diff(const Texture& a, const Texture& b)
    {
        if (a.get_size() != b.get_size())
        {
            throw std::runtime_error("diff: textures are not the same size");
        }

        auto s = a.get_size();
        auto result = Texture(s, ColorMode::RGBA, DataType::UINT8, nullptr, "diff");
        for (auto u = 0u; u < s.x; u++)
        {
            for (auto v = 0u; v < s.y; v++)
            {
                auto ac = a.get_texel({u, v});
                auto bc = b.get_texel({u, v});
                auto diff = glm::abs(ac - bc);
                diff.a = 1.0f - diff.a;
                result.set_texel({u, v}, diff);
            }
        }
        return result;
    }
}
