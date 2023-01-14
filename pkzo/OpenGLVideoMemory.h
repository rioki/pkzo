// pkzo
// Copyright 2022-2023 Sean Farrell
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

#pragma once
#include "config.h"

#include <rioki/glow/fwd.h>

namespace pkzo
{
    class Mesh;
    class Texture;
    class Material;

    enum class TextureFallback
    {
        WHITE,
        BLACK,
        NORMAL
    };

    class OpenGLVideoMemory
    {
    public:
        OpenGLVideoMemory() noexcept;
        ~OpenGLVideoMemory() = default;

        std::shared_ptr<glow::Shader> load_shader(unsigned int id) noexcept;
        std::shared_ptr<glow::VertexBuffer> upload(const std::shared_ptr<const Mesh>& mesh) noexcept;
        std::shared_ptr<glow::Texture> upload(const std::shared_ptr<const Texture>& texture, TextureFallback fallback) noexcept;
        std::shared_ptr<glow::Parameters> upload(const std::shared_ptr<const Material>& material) noexcept;

        void collect() noexcept;

    private:
        std::shared_ptr<Texture> black_fallback_texture;
        std::shared_ptr<Texture> white_fallback_texture;
        std::shared_ptr<Texture> normal_fallback_texture;

        using CacheKey = std::tuple<size_t, size_t>; // asset id + asset version

        template <typename GlObject, size_t StartAge = 10>
        struct CacheValue
        {
            size_t                    age = StartAge;
            std::shared_ptr<GlObject> object;

            CacheValue() noexcept = default;

            CacheValue(std::shared_ptr<GlObject>& obj) noexcept
            : object(obj) {}

            const std::shared_ptr<GlObject>& get() noexcept
            {
                age = StartAge;
                return object;
            }

            bool collect() noexcept
            {
                assert(age != 0);
                age--;
                return age == 0;
            }
        };

        std::map<unsigned int, std::shared_ptr<glow::Shader>> shaders;
        std::map<CacheKey, CacheValue<glow::VertexBuffer>>    vertex_buffers;
        std::map<CacheKey, CacheValue<glow::Texture>>         textures;
        std::map<CacheKey, CacheValue<glow::Parameters>>      materials;

        std::shared_ptr<Texture> get_fallback_texture(TextureFallback id) const noexcept;

        OpenGLVideoMemory(const OpenGLVideoMemory&) = delete;
        const OpenGLVideoMemory& operator = (const OpenGLVideoMemory&) = delete;
    };
}
