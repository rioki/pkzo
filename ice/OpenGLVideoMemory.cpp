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
#include "OpenGLVideoMemory.h"

#include <rioki/glow/glow.h>

#include "utils.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

namespace ice
{


    OpenGLVideoMemory::OpenGLVideoMemory() noexcept
    {
        black_fallback_texture  = make_black_texture();
        white_fallback_texture  = make_white_texture();
        normal_fallback_texture = make_normal_texture();
    }

    std::string LoadTextResource(HMODULE hModule, LPCWSTR lpName, LPCWSTR lpType)
    {
        auto hRSrc = FindResourceW(hModule, lpName, lpType);
        assert(hRSrc);
        auto hGlobal = LoadResource(hModule, hRSrc);
        assert(hGlobal);
        auto nSize = SizeofResource(hModule, hRSrc);
        auto psCode = reinterpret_cast<const char*>(LockResource(hGlobal));
        return std::string(psCode, nSize);
    }

    std::shared_ptr<glow::Shader> OpenGLVideoMemory::load_shader(unsigned int id) noexcept
    {
        static auto hModule = GetModuleHandleW(L"ice.dll");

        auto i = shaders.find(id);
        if (i != end(shaders))
        {
            return i->second;
        }

        try
        {
            auto code = LoadTextResource(hModule, MAKEINTRESOURCE(id), L"GLSL");
            auto shader = std::make_shared<glow::Shader>(code);
            shaders[id] = shader;

            return shader;
        }
        // This should only happen in development
        catch (const std::exception& ex)
        {
            show_message_box(MessageBoxIcon::ERROR, "GLSL Compile Error", ex.what());
            std::abort();
        }
    }

    std::shared_ptr<glow::VertexBuffer> OpenGLVideoMemory::upload(const std::shared_ptr<const Mesh>& mesh) noexcept
    {
        assert(mesh);

        auto i = vertex_buffers.find({mesh->get_id(), mesh->get_version()});
        if (i != end(vertex_buffers))
        {
            return i->second.get();
        }

        auto buffer = std::make_shared<glow::VertexBuffer>();
        buffer->upload_values(glow::VERTEX,   mesh->get_vertices());
        buffer->upload_values(glow::NORMAL,   mesh->get_normals());
        //buffer->upload_values(glow::TANGENT,   mesh->get_tangents());
        buffer->upload_values(glow::TEXCOORD, mesh->get_texcoords());
        buffer->upload_indexes(mesh->get_faces());

        vertex_buffers[{mesh->get_id(), mesh->get_version()}] = buffer;

        return buffer;
    }

    std::shared_ptr<glow::Texture> OpenGLVideoMemory::upload(const std::shared_ptr<const Texture>& texture, TextureFallback fallback) noexcept
    {
        if (texture == nullptr)
        {
            return upload(get_fallback_texture(fallback), fallback);
        }

        auto i = textures.find({texture->get_id(), texture->get_version()});
        if (i != end(textures))
        {
            return i->second.get();
        }

        auto size   = texture->get_size();
        auto color  = static_cast<glow::ColorMode>(texture->get_color_mode());
        auto data   = static_cast<glow::DataType>(texture->get_data_type());
        auto bits   = texture->get_data();
        auto filter = static_cast<glow::FilterMode>(texture->get_filter_mode());
        auto wrap   = static_cast<glow::WrapMode>(texture->get_wrap_mode());

        auto gl_texture = std::make_shared<glow::Texture>();
        gl_texture->upload_2d(size, color, data, bits, filter, wrap);

        textures[{texture->get_id(), texture->get_version()}] = gl_texture;

        return gl_texture;
    }

    std::shared_ptr<glow::Parameters> OpenGLVideoMemory::upload(const std::shared_ptr<const Material>& material) noexcept
    {
        assert(material);

        auto i = materials.find({material->get_id(), material->get_version()});
        if (i != end(materials))
        {
            return i->second.get();
        }

        auto params = glow::make_shared_parameters({
            {"ice_BaseColorFactor", material->get_base_color_factor()},
            {"ice_BaseColorMap",    upload(material->get_base_color_map(), TextureFallback::WHITE)},
            {"ice_EmissiveFactor",  material->get_emissive_factor()},
            {"ice_EmissiveMap",     upload(material->get_emissive_map(), TextureFallback::WHITE)}
        });

        materials[{material->get_id(), material->get_version()}] = params;

        return params;
    }

    template <typename Col>
    void glcollect(Col& col)
    {
        auto i = begin(col);
        while (i != end(col))
        {
            auto e = i->second.collect();
            if (e)
            {
                i = col.erase(i);
            }
            else
            {
                i++;
            }
        }
    }

    void OpenGLVideoMemory::collect() noexcept
    {
        glcollect(vertex_buffers);
        glcollect(textures);
        glcollect(materials);
    }

    std::shared_ptr<Texture> OpenGLVideoMemory::get_fallback_texture(TextureFallback id) const noexcept
    {
        switch (id)
        {
            case TextureFallback::WHITE:
                assert(white_fallback_texture);
                return white_fallback_texture;
            case TextureFallback::BLACK:
                assert(black_fallback_texture);
                return black_fallback_texture;
            case TextureFallback::NORMAL:
                assert(normal_fallback_texture);
                return normal_fallback_texture;
            default:
                std::terminate();
        }
    }
}
