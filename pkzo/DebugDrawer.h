// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_DEBUG_DRAWER_H_
#define _PKZO_DEBUG_DRAWER_H_

#include <memory>
#include <queue>
#include <glm/glm.hpp>

#include "System.h"

namespace pkzo
{
    class Engine;
    class Shader;
    class Mesh;
    class Camera;

    //! System available to draw debug info into the scene.
    class DebugDrawer : public System
    {
    public:

        DebugDrawer(Engine& engine);

        //! Draw a line
        void draw_line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color);
        //! Draw a line
        void draw_line(const glm::vec3& start, const glm::vec3& end, const glm::vec4& start_color, const glm::vec4& end_color);

        void tick(float dt) override;

        void draw(Camera& camera);

    private:
        Engine&                 engine;
        glm::mat4               projection;
        glm::mat4               model_view;
        std::unique_ptr<Shader> line_shader;
        std::unique_ptr<Mesh>   line_mesh;

        struct Line
        {
            glm::vec3 start;
            glm::vec3 end;
            glm::vec4 start_color;
            glm::vec4 end_color;
        };
        std::queue<Line> lines;
    };
}

#endif
