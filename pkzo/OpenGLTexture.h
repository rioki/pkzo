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

#include "Texture.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace pkzo
{
    class PKZO_EXPORT OpenGLTexture : public Texture
    {
    public:
        static std::shared_ptr<OpenGLTexture> create(const CreateSpecs& specs);
        static std::shared_ptr<OpenGLTexture> create(const glm::vec4& color, const std::string& id = "Static Color");

        OpenGLTexture(const CreateSpecs& specs);
        OpenGLTexture(const std::shared_ptr<Texture>& source);
        ~OpenGLTexture();

        const std::string& get_id() const override;
        glm::uvec2 get_size() const override;
        ColorMode get_color_mode() const override;
        DataType get_data_type() const override;
        const void* get_memory() const override;
        TextureFilter get_filter() const override;
        Clamp get_clamp() const override;

        GLuint get_handle() const;

        void bind(int slot);

    private:
        std::string id;
        glm::uvec2  size;
        ColorMode   color_mode;
        DataType    data_type;
        TextureFilter filter;
        Clamp         clamp;
        GLuint      handle;
    };
}
