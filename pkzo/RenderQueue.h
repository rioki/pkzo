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

    enum BlendMode
    {
        NONE,
        ALPHA,
        ADITIVE
    };

    //! Render Queue
    class RenderQueue : private stdex::non_copyable
    {
    public:
        //! Construct a render queue.
        RenderQueue();

        //! Reset the queue.
        void clear();

        //! Set orhto projection.
        void set_othro_camera(float left, float right, float bottom, float top, float near, float far);

        //! Submit rectangle for drawing
        void submit_rectangle(const glm::mat4& model_matrix, const glm::vec2& size, const std::shared_ptr<Material>& material, const glm::mat3& texture_matrix = glm::mat3(1.0f));

        //! Execute the pending render commands.
        void execute(BlendMode blend_mode);

    private:
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

        std::shared_ptr<Mesh> rectangle_mesh;
    };
}

#endif
