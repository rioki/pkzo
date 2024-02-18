
#include "pch.h"

#include <glow/glow.h>
#include <pkzo/Window.h>

glow::ColorMode to_glow(pkzo::ColorMode mode)
{
    switch (mode)
    {
        case pkzo::ColorMode::RGB:
            return glow::ColorMode::RGB;
        case pkzo::ColorMode::BGR:
            return glow::ColorMode::BGR;
        case pkzo::ColorMode::RGBA:
            return glow::ColorMode::RGBA;
        case pkzo::ColorMode::BGRA:
            return glow::ColorMode::BGRA;
        default:
            throw std::runtime_error("Invalid color mode");
    }
}

TEST(OpenGL, compile_shader)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, testing::get_test_name(), glm::uvec2(800u, 600u), pkzo::WindowMode::WINDOWED};

    auto vertex_code = R"(
        #version 430

        in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";

    auto fragment_code = R"(
        #version 430

        out vec4 oFragColor;

        void main()
        {
            oFragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
    )";

    auto shader = glow::Shader("compile_shader");
    shader.compile(glow::ShaderType::VERTEX, vertex_code);
    shader.compile(glow::ShaderType::FRAGMENT, fragment_code);
    shader.link();
}

TEST(OpenGL, upload_rectangle_and_render_it)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, testing::get_test_name(), glm::uvec2(800u, 600u), pkzo::WindowMode::WINDOWED};

    auto vertex_code = R"(
        #version 430

        in vec3 aPosition;

        uniform mat4 uProjection;
        uniform mat4 uView;
        uniform mat4 uModel;

        void main()
        {
            gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
        }
    )";

    auto fragment_code = R"(
        #version 430

        out vec4 oFragColor;

        void main()
        {
            oFragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
    )";

    auto shader = glow::Shader("upload_rectangle_and_render_it");
    shader.compile(glow::ShaderType::VERTEX, vertex_code);
    shader.compile(glow::ShaderType::FRAGMENT, fragment_code);
    shader.link();

    auto extend = glm::vec2(250, 150);
    auto positions = std::vector<glm::vec3>{
        {-extend.x, -extend.y, 0.0f},
        { extend.x, -extend.y, 0.0f},
        { extend.x,  extend.y, 0.0f},
        {-extend.x,  extend.y, 0.0f}
    };

    auto faces = std::vector<glm::uvec3>{
        {0, 1, 2},
        {2, 3, 0}
    };

    auto vertex_buffer = glow::VertexBuffer();

    vertex_buffer.upload_values("aPosition", positions);
    vertex_buffer.upload_indexes(faces);

    window.on_draw([&] () {
        shader.bind();
        shader.set_uniform("uProjection", glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, -1.0f, 1.0f));
        shader.set_uniform("uView", glm::mat4(1.0f));
        shader.set_uniform("uModel", glm::mat4(1.0f));

        vertex_buffer.bind(shader);
        vertex_buffer.draw();
    });

    window.draw();
    window.draw();

    EXPECT_IMAGE_REF_EQ(window.get_screenshot());
}

TEST(OpenGL, upload_texture_and_render_it)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, testing::get_test_name(), glm::uvec2(800u, 600u), pkzo::WindowMode::WINDOWED};

    auto vertex_code = R"(
        #version 430

        in vec3 aPosition;
        in vec2 aTexCoord;

        out vec2 vTexCoord;

        uniform mat4 uProjection;
        uniform mat4 uView;
        uniform mat4 uModel;

        void main()
        {
            gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
            vTexCoord = aTexCoord;
        }
    )";

    auto fragment_code = R"(
        #version 430

        in vec2 vTexCoord;

        out vec4 oFragColor;

        uniform sampler2D uTexture;

        void main()
        {
            oFragColor = texture(uTexture, vTexCoord);
        }
    )";

    auto shader = glow::Shader("upload_texture_and_render_it");
    shader.compile(glow::ShaderType::VERTEX, vertex_code);
    shader.compile(glow::ShaderType::FRAGMENT, fragment_code);
    shader.link();

    auto cat = pkzo::Image(testing::get_test_input() / "textures/AngryCat.png");
    auto texture = glow::Texture();
    texture.upload(cat.get_size(), glow::ColorMode::BGRA, glow::DataType::UINT8, cat.get_data());

    auto extend = glm::vec2(250, 150);
    auto positions = std::vector<glm::vec3>{
        {-extend.x, -extend.y, 0.0f},
        { extend.x, -extend.y, 0.0f},
        { extend.x,  extend.y, 0.0f},
        {-extend.x,  extend.y, 0.0f}
    };

    auto tex_coords = std::vector<glm::vec2>{
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}
    };

    auto faces = std::vector<glm::uvec3>{
        {0, 1, 2},
        {2, 3, 0}
    };

    auto vertex_buffer = glow::VertexBuffer();

    vertex_buffer.upload_values("aPosition", positions);
    vertex_buffer.upload_values("aTexCoord", tex_coords);
    vertex_buffer.upload_indexes(faces);

    window.on_draw([&] () {
        shader.bind();
        shader.set_uniform("uProjection", glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, -1.0f, 1.0f));
        shader.set_uniform("uView", glm::mat4(1.0f));
        shader.set_uniform("uModel", glm::mat4(1.0f));
        shader.set_uniform("uTexture", 0);

        texture.bind(0);

        vertex_buffer.bind(shader);
        vertex_buffer.draw();
    });

    window.draw();
    window.draw();

    EXPECT_IMAGE_REF_EQ(window.get_screenshot());
}

TEST(OpenGL, render_pipeline_singlpass)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, testing::get_test_name(), glm::uvec2(800u, 600u), pkzo::WindowMode::WINDOWED};

    auto pipeline = glow::Pipeline();

    auto global_parameters = glow::make_shared_parameters({
        {"uProjection", glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, -1.0f, 1.0f)},
        {"uView",       glm::mat4(1.0f)}
    });
    pipeline.set_parameters(global_parameters);

    auto vertex_code = R"(
        #version 430

        in vec3 aPosition;
        in vec2 aTexCoord;

        out vec2 vTexCoord;

        uniform mat4 uProjection;
        uniform mat4 uView;
        uniform mat4 uModel;

        void main()
        {
            gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
            vTexCoord = aTexCoord;
        }
    )";

    auto fragment_code = R"(
        #version 430

        in vec2 vTexCoord;

        out vec4 oFragColor;

        uniform sampler2D uTexture;

        void main()
        {
            oFragColor = texture(uTexture, vTexCoord);
        }
    )";

    auto shader = std::make_shared<glow::Shader>("Solid Pass");
    shader->compile(glow::ShaderType::VERTEX, vertex_code);
    shader->compile(glow::ShaderType::FRAGMENT, fragment_code);
    shader->link();

    pipeline.add_pass("Solid Pass", glow::PassType::GEOMETRY, shader);

    auto extend = glm::vec2(200, 100);
    auto positions = std::vector<glm::vec3>{
        {-extend.x, -extend.y, 0.0f},
        { extend.x, -extend.y, 0.0f},
        { extend.x,  extend.y, 0.0f},
        {-extend.x,  extend.y, 0.0f}
    };

    auto tex_coords = std::vector<glm::vec2>{
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}
    };

    auto faces = std::vector<glm::uvec3>{
        {0, 1, 2},
        {2, 3, 0}
    };

    auto vertex_buffer = std::make_shared<glow::VertexBuffer>();

    vertex_buffer->upload_values("aPosition", positions);
    vertex_buffer->upload_values("aTexCoord", tex_coords);
    vertex_buffer->upload_indexes(faces);

    auto cat = pkzo::Image(testing::get_test_input() / "textures/AngryCat.png");
    auto cm  = to_glow(cat.get_color_mode());
    auto texture = std::make_shared<glow::Texture>();
    texture->upload(cat.get_size(), cm, glow::DataType::UINT8, cat.get_data());

    auto geom_parameters = glow::make_shared_parameters({
        {"uModel", glm::mat4(1.0f)},
        {"uTexture", texture}
    });

    pipeline.add_geometry(vertex_buffer, geom_parameters);

    window.on_draw([&] () {
        pipeline.execute();
    });

    window.draw();
    window.draw();

    EXPECT_IMAGE_REF_EQ(window.get_screenshot());
}
