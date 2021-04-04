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

#ifndef _ICE_TEXTURE_H_
#define _ICE_TEXTURE_H_

#include "config.h"

#include <memory>
#include <filesystem>
#include <glm/fwd.hpp>

#include "SdlSentry.h"

struct SDL_Surface;

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

    class TextureImpl;
    class GraphicTextureImpl;

    //! 2D Image
    class PKZO_EXPORT Texture
    {
    public:
        //! Load texture form file.
        //!
        //! @param file the file to load the texture from.
        Texture(const std::filesystem::path& file);
        //! Create texture from memory buffer.
        Texture(const glm::uvec2& size, ColorMode mode, DataType type, const void* memory, const std::string& label = "memory");

        Texture(SDL_Surface* surface, const std::string& label = "memory") noexcept;
        Texture(const Texture&) = delete;
        Texture(Texture&& other) noexcept;
        ~Texture();
        Texture& operator = (const Texture&) = delete;
        Texture& operator = (Texture&& other) noexcept;

        //! Get the texture size.
        glm::uvec2 get_size() const noexcept;
        //! Get the color mode.
        ColorMode get_color_mode() const noexcept;
        //! Get the data type.
        DataType get_data_type() const noexcept;

        //! Get the color value from the given texel.
        glm::vec4 get_texel(const glm::uvec2& index) const noexcept;
        //! Set the color value of a the given text.
        void set_texel(const glm::uvec2& index, const glm::vec4& value) noexcept;

        //! Get the data buffer.
        void* get_data() const noexcept;

        //! Upload the texture to VRAM
        void upload() noexcept;
        //! Bind the texture to a given slot for rendering.
        void bind(glm::uint slot) noexcept;

        //! Save file to disk.
        void save(const std::filesystem::path& file) const;

    private:
        std::unique_ptr<TextureImpl> impl;
        std::unique_ptr<GraphicTextureImpl> graphic_impl;
    };

    //! Compare Textures
    //!
    //! This function will compare two images and return a error score.
    //!
    //! @param a the first image
    //! @param b the second image
    //! @return an error score
    PKZO_EXPORT float compare(const Texture& a, const Texture& b);

    //! Create a difference of two textures.
    PKZO_EXPORT Texture diff(const Texture& a, const Texture& b);
}

#endif
