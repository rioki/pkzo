// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "ScreenRenderer.h"

#include "resource.h"
#include "glm_2d.h"
#include "utils.h"

namespace ice
{
    constexpr auto COLOR       = "pkzo_Color";
    constexpr auto HAS_TEXTURE = "pkzo_HasTexture";
    constexpr auto TEXTURE     = "pkzo_Texture";

    // TMP: this is a workaround to keep the rendering working. -> GraphicSystem / VideoMemory?
    std::shared_ptr<glow::Texture> upload(const std::shared_ptr<Texture>& texture)
    {
        static std::map<Texture*, std::weak_ptr<glow::Texture>> cache;

        if (!texture)
        {
            return {};
        }

        auto tx = cache.find(texture.get());
        if (tx != end(cache))
        {
            auto gl_texture = tx->second.lock();
            if (gl_texture)
            {
                return gl_texture;
            }
        }

        auto size   = texture->get_size();
        auto color  = static_cast<glow::ColorMode>(texture->get_color_mode());
        auto data   = static_cast<glow::DataType>(texture->get_data_type());
        auto bits   = texture->get_data();
        auto filter = static_cast<glow::FilterMode>(texture->get_filter_mode());
        auto wrap   = static_cast<glow::WrapMode>(texture->get_wrap_mode());

        auto gl_texture = std::make_shared<glow::Texture>();
        gl_texture->upload_2d(size, color, data, bits, filter, wrap);
        cache[texture.get()] = gl_texture;
        return gl_texture;
    }

    void ScreenRenderer::Rectangle::set_transform(const glm::mat3& value) noexcept
    {
        transform = value;
        pipeline.update_geometry(handle, create_3d_transform());
    }

    const glm::mat3& ScreenRenderer::Rectangle::get_transform() const noexcept
    {
        return transform;
    }

    void ScreenRenderer::Rectangle::set_size(const glm::vec2& value) noexcept
    {
        size = value;
        pipeline.update_geometry(handle, create_3d_transform());
    }

    const glm::vec2& ScreenRenderer::Rectangle::get_size() const noexcept
    {
        return size;
    }

    void ScreenRenderer::Rectangle::set_color(const glm::vec4& value) noexcept
    {
        color = value;
        pipeline.update_geometry(handle, create_parameters());
    }

    const glm::vec4& ScreenRenderer::Rectangle::get_color() const noexcept
    {
        return color;
    }

    void ScreenRenderer::Rectangle::set_texture(const std::shared_ptr<Texture>& value) noexcept
    {
        texture = value;
        pipeline.update_geometry(handle, create_parameters());
    }

    const std::shared_ptr<Texture>& ScreenRenderer::Rectangle::get_texture() const noexcept
    {
        return texture;
    }

    ScreenRenderer::Rectangle::Rectangle(glow::Pipeline& _pipeline, const glm::mat3& _transform, const glm::vec2& _size, const glm::vec4& _color, const std::shared_ptr<Texture>& _texture) noexcept
    : pipeline(_pipeline), transform(_transform), size(_size), color(_color), texture(_texture)
    {
        handle = pipeline.add_geometry(create_3d_transform(), create_unit_rectangle(), create_parameters());
    }

    ScreenRenderer::Rectangle::~Rectangle()
    {
        pipeline.remove_geometry(handle);
        handle = 0;
    }

    glm::mat4 ScreenRenderer::Rectangle::create_3d_transform() const noexcept
    {
        return glm::to3d(glm::scale(transform, size));
    }

    std::shared_ptr<glow::VertexBuffer> ScreenRenderer::Rectangle::create_unit_rectangle()
    {
        static auto cache = std::weak_ptr<glow::VertexBuffer>();

        auto mesh = cache.lock();
        if (mesh)
        {
            return mesh;
        }

        auto vertexes = std::vector<glm::vec3>{
            {-0.5f, -0.5f, 0.0f},
            {-0.5f,  0.5f, 0.0f},
            { 0.5f,  0.5f, 0.0f},
            { 0.5f, -0.5f, 0.0f}
        };

        auto textcoord = std::vector<glm::vec2>{
            {0.0f, 0.0f},
            {0.0f, 1.0f},
            {1.0f, 1.0f},
            {1.0f, 0.0f}
        };

        auto indexes = std::vector<glm::uvec3>{
            {0, 1, 2},
            {2, 3, 0}
        };

        mesh = std::make_shared<glow::VertexBuffer>();
        mesh->upload_values(glow::VERTEX, vertexes);
        mesh->upload_values(glow::TEXCOORD, textcoord);
        mesh->upload_indexes(indexes);

        cache = mesh;
        return mesh;
    }

    std::shared_ptr<glow::Parameters> ScreenRenderer::Rectangle::create_parameters() const noexcept
    {
        return texture ?
            glow::make_shared_parameters({
                {COLOR,       color},
                {HAS_TEXTURE, true},
                {TEXTURE,     upload(texture)}
            }) :
            glow::make_shared_parameters({
                {COLOR,       color},
                {HAS_TEXTURE, false}
            });
    }

    ScreenRenderer::ScreenRenderer() noexcept = default;

    ScreenRenderer::~ScreenRenderer() = default;;

    void ScreenRenderer::set_screen_size(const glm::vec2& value)
    {
        size = value;
    }

    ScreenRenderer::Rectangle* ScreenRenderer::add_rectangle(const glm::mat3& transform, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture>& texture)
    {
        assert(pipeline);
        return add_unique_ptr<Rectangle>(geometries, *pipeline, transform, size, color, texture);
    }

    void ScreenRenderer::remove_geometry(ScreenRenderer::Rectangle* rectangle)
    {
        remove_unique_ptr(geometries, rectangle);
    }

    void ScreenRenderer::render()
    {
        assert(pipeline);

        auto hs = size / 2.0f;

        auto proj = glm::ortho(-hs.x, hs.x, -hs.y, hs.y);
        auto view = glm::mat4(1.0f);

        pipeline->set_camera(proj, view);
        pipeline->execute();
    }

    // TODO Use AssetLibrary to dedup shaders
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

    auto load_shader(HMODULE hModule, unsigned int rcid)
    {
        auto code = LoadTextResource(hModule, MAKEINTRESOURCE(rcid), L"GLSL");
        return std::make_shared<glow::Shader>(code);
    }

    std::unique_ptr<glow::Pipeline> ScreenRenderer::create_pipeline()
    {
        HMODULE hModule = GetModuleHandleW(L"ice.dll");
        assert(hModule);

        auto pipeline = std::make_unique<glow::Pipeline>();

        pipeline->add_pass(glow::PassType::GEOMETRY, load_shader(hModule, IDR_GLSL_SCREEN), glow::DepthTest::OFF, glow::Blending::ALPHA);

        return pipeline;
    }
}
