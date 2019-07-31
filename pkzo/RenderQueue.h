// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_RENDER_QUEUE_H_
#define _PKZO_RENDER_QUEUE_H_

#include "defines.h"

#include <glm/glm.hpp>

#include "stdex.h"

namespace pkzo
{
    class Mesh;
    class Material;

    enum class RenderAlgorithm
    {
        UNLIT,
        LIT_FORWARD,
        LIT_DEFERRED
    };

    //! Render Queue
    class RenderQueue : private stdex::non_copyable
    {
    public:
        //! Construct a render queue.
        RenderQueue(const glm::uvec2& resolution);

        //! Reset the queue.
        void clear();

        //! Set the rendering resolution.
        void set_resolution(const glm::uvec2& value);

        //! Set orhto projection.
        void set_othro_camera(float left, float right, float bottom, float top, float near, float far);

        //! Set perspective camera projection
        void set_perspective_camera(const glm::mat4& transform, float fov);

        //! Submit rectangle for drawing
        void submit_rectangle(const glm::mat4& model_matrix, const glm::vec2& size, const std::shared_ptr<Material>& material, const glm::mat3& texture_matrix = glm::mat3(1.0f));

        //! Submit box for drawing
        void submit_box(const glm::mat4& model_matrix, const glm::vec3& size, const std::shared_ptr<Material>& material, const glm::mat3& texture_matrix = glm::mat3(1.0f));

        //! Submit mesh for drawing
        void submit_mesh(const glm::mat4& model_matrix, std::shared_ptr<Mesh> mesh, const std::shared_ptr<Material>& material, const glm::mat3& texture_matrix = glm::mat3(1.0f));

        //! Submit ambient light.
        void submit_ambient_light(const glm::vec3& color);

        //! Submit directional light.
        void submit_directional_light(const glm::vec3& color, const glm::vec3& direction);

        //! Submit point light.
        void submit_point_light(const glm::vec3& color, const glm::vec3& position);

        //! Submit spot light.
        void submit_spot_light(const glm::vec3& color, const glm::vec3& position, const glm::vec3& direction, float angle);

        //! Execute the pending render commands.
        void execute(RenderAlgorithm algorithm);

    private:
        glm::uvec2 resolution;
        glm::mat4 projection_matrix;
        glm::mat4 view_matrix;

        struct Geometry
        {
            glm::mat4 model_matrix;
            glm::mat3 texture_matrix;
            std::shared_ptr<Mesh> mesh;
            std::shared_ptr<Material> material;
        };
        std::list<Geometry> geometry;

        enum LightType
        {
            AMBIENT_LIGHT,
            DIRECTIONAL_LIGHT,
            POINT_LIGHT,
            SPOT_LIGHT
        };
        struct Light
        {
            glm::uint type;
            glm::vec3 color;
            glm::vec3 position;
            glm::vec3 direction;
            float angle;
        };
        std::list<Light> lights;

        std::shared_ptr<Mesh> rectangle_mesh;
        std::shared_ptr<Mesh> box_mesh;

        void draw_unlit_geometry();
        void draw_lit_geometry();
    };
}

#endif
