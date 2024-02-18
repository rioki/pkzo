// OpenGL Object Wrapper
// Copyright 2016-2022 Sean Farrell <sean.farrell@rioki.org>
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

#pragma once

#include <memory>
#include <variant>
#include <map>
#include <glm/glm.hpp>

#include "defines.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "Parameters.h"
#include "FrameBuffer.h"

namespace glow
{
    enum class PassType
    {
        FULLSCREEN,
        GEOMETRY,
        LIGHTS,
        LIGHTS_AND_GEOMETRY,
        GEOMETRY_AND_LIGHTS
        // SHADOW            // TODO for each light but camera = light source
    };

    enum class DepthTest
    {
        OFF,
        READ_ONLY,
        ON
    };

    enum class Blending
    {
        OFF,
        ALPHA,
        MULTIPASS
    };

    class GLOW_EXPORT Pipeline
    {
    public:
        Pipeline() noexcept;
        ~Pipeline();

        void set_parameters(const std::shared_ptr<Parameters>& parameters) noexcept;

        void add_pass(const std::string& label, PassType type, const std::shared_ptr<Shader>& shader) noexcept;
        void add_pass(const std::string& label, PassType type, const std::shared_ptr<Shader>& shader, DepthTest depth_test, Blending blending) noexcept;
        void add_pass(const std::string& label, PassType type, const std::shared_ptr<Shader>& shader, DepthTest depth_test, Blending blending, const std::shared_ptr<Parameters>& parameters) noexcept;
        void add_pass(const std::string& label, PassType type, const std::shared_ptr<FrameBuffer>& buffer, const std::shared_ptr<Shader>& shader) noexcept;
        void add_pass(const std::string& label, PassType type, const std::shared_ptr<FrameBuffer>& buffer, const std::shared_ptr<Shader>& shader, DepthTest depth_test, Blending blending) noexcept;
        void add_pass(const std::string& label, PassType type, const std::shared_ptr<FrameBuffer>& buffer, const std::shared_ptr<Shader>& shader, DepthTest depth_test, Blending blending, const std::shared_ptr<Parameters>& parameters) noexcept;

        unsigned int add_geometry(const std::shared_ptr<VertexBuffer>& mesh, const std::shared_ptr<Parameters>& parameters) noexcept;
        void remove_geometry(unsigned int id) noexcept;

        void remove_all_geometry() noexcept;

        unsigned int add_light(const std::shared_ptr<Parameters>& parameters) noexcept;
        unsigned int get_light_count() const noexcept;
        void remove_light(unsigned int id) noexcept;

        void remove_all_light() noexcept;

        void execute() noexcept;

    private:
        struct Pass
        {
            std::string                  label;
            PassType                     type;
            std::shared_ptr<FrameBuffer> buffer;
            std::shared_ptr<Shader>      shader;
            DepthTest                    depth_test;
            Blending                     blending;
            std::shared_ptr<Parameters>  parameters;
        };

        struct Geometry
        {
            std::shared_ptr<VertexBuffer> mesh;
            std::shared_ptr<Parameters>   parameters;
        };

        struct Light
        {
            std::shared_ptr<Parameters> parameters;
        };

        std::unique_ptr<VertexBuffer> fullscreen_rectangle = make_fullscreen_rectangle();

        std::shared_ptr<Parameters> parameters;
        std::vector<Pass> passes;

        unsigned int last_geom_id = 0;
        std::map<unsigned int, Geometry> geoms;
        unsigned int last_light_id = 0;
        std::map<unsigned int, Light> lights;

        static std::unique_ptr<VertexBuffer> make_fullscreen_rectangle() noexcept;

        Pipeline(const Pipeline& orig) = delete;
        Pipeline& operator = (const Pipeline& orig) = delete;

        friend void apply(Shader& shader, Light& light) noexcept;
        friend void apply(Shader& shader, Geometry& geom) noexcept;
    };
}
