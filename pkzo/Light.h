// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_LIGHT_H_
#define _PKZO_LIGHT_H_

#include "SceneNode.h"

namespace pkzo
{
    class Mesh;
    class Material;
    class Camera;
    class FrameBuffer;

    /*!
     * Geometry
     */
    class PKZO_EXPORT Light : public SceneNode
    {
    public:
        Light();
        ~Light();

        /*!
         * The mesh
         *
         * @{
         */
        void set_mesh(std::shared_ptr<Mesh> value);
        std::shared_ptr<Mesh> get_mesh() const;
        /*! @} */

        /*!
         * The material
         *
         * @{
         */
        void set_material(std::shared_ptr<Material> value);
        std::shared_ptr<Material> get_material();
        /*! @} */

        void draw(const Camera& camera, FrameBuffer& gbuffer);

    private:
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;
    };
}

#endif
