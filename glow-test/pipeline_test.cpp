
#include "pch.h"

#include <glow/glow.h>
#include <pkzo/Window.h>

std::shared_ptr<glow::VertexBuffer> create_rectangle(const glm::vec2& size)
{
    auto extend = size / 2.0f;
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

    return vertex_buffer;
}

glow::ColorMode to_glow(pkzo::ColorMode mode);

std::shared_ptr<glow::Texture> load_texture(const std::filesystem::path& file)
{
    auto image = pkzo::Image(file);
    auto cm  = to_glow(image.get_color_mode());
    auto texture = std::make_shared<glow::Texture>();
    texture->upload(image.get_size(), cm, glow::DataType::UINT8, image.get_data());
    return texture;
}

TEST(Pipeline, render_to_framebuffer)
{
    auto event_router = pkzo::EventRouter{};
    auto window = pkzo::Window{event_router, testing::get_test_name(), glm::uvec2(800u, 600u), pkzo::WindowMode::WINDOWED};

    std::unique_ptr<glow::Pipeline> pipeline;

    window.init([&](){
        glow::init();

        pipeline = std::make_unique<glow::Pipeline>();

        pipeline->set_parameters(glow::make_shared_parameters({
            {"uProjection", glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, -1.0f, 1.0f)},
            {"uView",       glm::mat4(1.0f)}
        }));

        auto config = std::vector<glow::BufferConfig>{
            {"uColor", "oFragColor", glow::ColorMode::RGB,  glow::DataType::UINT8}
        };

        auto frame_buffer = std::make_shared<glow::FrameBuffer>(window.get_size(), config);

        // first pass: render angry cat to frame buffer
        auto pass1_vertex_code = R"(
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
        auto pass1_fragment_code = R"(
            #version 430

            in vec2 vTexCoord;

            out vec4 oFragColor;

            uniform sampler2D uTexture;

            void main()
            {
                oFragColor = texture(uTexture, vTexCoord);
            }
        )";

        auto pass1_shader = std::make_shared<glow::Shader>("color");
        pass1_shader->compile(glow::ShaderType::VERTEX, pass1_vertex_code);
        pass1_shader->compile(glow::ShaderType::FRAGMENT, pass1_fragment_code);
        pass1_shader->link();

        pipeline->add_pass("color", glow::PassType::GEOMETRY, frame_buffer, pass1_shader);

        // second pass: apply blur to frame buffer
        auto pass2_vertex_code = R"(
            #version 430

            in vec3 aPosition;
            in vec2 aTexCoord;

            out vec2 vTexCoord;

            void main()
            {
                gl_Position = vec4(aPosition, 1.0);
                vTexCoord = aTexCoord;
            }
        )";

        auto pass2_fragment_code = R"(
            #version 430

            in vec2 vTexCoord;

            out vec4 oFragColor;

            uniform sampler2D uColor;
            uniform ivec2 uFrameBufferSize;

            float radius = 3.0;

            void main()
            {
                vec4 sum = vec4(0.0);

                vec2 tc = vTexCoord;

                vec2 blur = vec2(radius)/uFrameBufferSize;

                sum += texture2D(uColor, vec2(vTexCoord.x - 4.0 * blur.x, vTexCoord.y - 4.0 * blur.y)) * 0.0162162162;
                sum += texture2D(uColor, vec2(vTexCoord.x - 3.0 * blur.x, vTexCoord.y - 3.0 * blur.y)) * 0.0540540541;
                sum += texture2D(uColor, vec2(vTexCoord.x - 2.0 * blur.x, vTexCoord.y - 2.0 * blur.y)) * 0.1216216216;
                sum += texture2D(uColor, vec2(vTexCoord.x - 1.0 * blur.x, vTexCoord.y - 1.0 * blur.y)) * 0.1945945946;

                sum += texture2D(uColor, vec2(vTexCoord.x, vTexCoord.y)) * 0.2270270270;

                sum += texture2D(uColor, vec2(vTexCoord.x + 1.0 * blur.x, vTexCoord.y + 1.0 * blur.y)) * 0.1945945946;
                sum += texture2D(uColor, vec2(vTexCoord.x + 2.0 * blur.x, vTexCoord.y + 2.0 * blur.y)) * 0.1216216216;
                sum += texture2D(uColor, vec2(vTexCoord.x + 3.0 * blur.x, vTexCoord.y + 3.0 * blur.y)) * 0.0540540541;
                sum += texture2D(uColor, vec2(vTexCoord.x + 4.0 * blur.x, vTexCoord.y + 4.0 * blur.y)) * 0.0162162162;

                oFragColor = sum;
            }
        )";

        auto pass2_shader = std::make_shared<glow::Shader>("blur");
        pass2_shader->compile(glow::ShaderType::VERTEX, pass2_vertex_code);
        pass2_shader->compile(glow::ShaderType::FRAGMENT, pass2_fragment_code);
        pass2_shader->link();

        pipeline->add_pass("blur", glow::PassType::FULLSCREEN, pass2_shader, glow::DepthTest::OFF, glow::Blending::OFF, frame_buffer->get_input_parameters());


        auto vertex_buffer = create_rectangle(glm::vec2(300, 200));
        auto geom_parameters = glow::make_shared_parameters({
            {"uModel", glm::mat4(1.0f)},
            {"uTexture", load_texture(testing::get_test_input() / "textures/AngryCat.png")}
        });
        pipeline->add_geometry(vertex_buffer, geom_parameters);

    });

    window.on_draw([&](){
        pipeline->execute();
    });

    window.draw();
    window.draw();

    EXPECT_IMAGE_REF_EQ(window.get_screenshot());
}
