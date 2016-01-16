
#include "AtriumScene.h"

using pkzo::Color;
using pkzo::Vector3;
using pkzo::Quaternion;

namespace atrium
{
    AtriumScene::AtriumScene(pkzo::Library& lib)
    {
        ambient_light.set_color(Color(0.05f, 0.05f, 0.05f));
        add_node(ambient_light);

        sun_light.set_color(Color(0.5f, 0.5f, 0.5f));
        sun_light.set_orientation(pkzo::Quaternion::axis_angle(-135, pkzo::Vector3(0, 0, 1)) * 
                                  pkzo::Quaternion::axis_angle(20, pkzo::Vector3(1, 0, 0)));
        add_node(sun_light);

        sky.set_cubemap(lib.load_cubemap("../assets/textures/CloudyAfternoon.jcm"));
        add_node(sky);

        auto colum_mesh   = lib.load_mesh("../assets/meshes/Column.ply");
        auto ground2_mesh = lib.load_mesh("../assets/meshes/Ground2.ply");
        auto wall2_mesh   = lib.load_mesh("../assets/meshes/Wall2.ply");

        auto white      = lib.load_material("../assets/materials/White.jmn");
        
        // columns
        for (unsigned int i = 0; i < 6; i++)
        {
            pkzo::Geometry* column = new pkzo::Geometry;
            column->set_mesh(colum_mesh);
            column->set_material(white);
            column->set_position(Vector3(-5.0f + (float)i * 2.0f, -2.3f, 0.0f));
            add_node(*column);
            static_objets.push_back(column);

            column = new pkzo::Geometry;
            column->set_mesh(colum_mesh);
            column->set_material(white);
            column->set_position(Vector3(-5.0f + (float)i * 2.0f, 2.3f, 0.0f));
            add_node(*column);
            static_objets.push_back(column);

            column = new pkzo::Geometry;
            column->set_mesh(colum_mesh);
            column->set_material(white);
            column->set_position(Vector3(-5.0f + (float)i * 2.0f, -2.3f, 3.2f));
            add_node(*column);
            static_objets.push_back(column);

            column = new pkzo::Geometry;
            column->set_mesh(colum_mesh);
            column->set_material(white);
            column->set_position(Vector3(-5.0f + (float)i * 2.0f, 2.3f, 3.2f));
            add_node(*column);
            static_objets.push_back(column);
        }

        // floor
        for (unsigned int i = 0; i < 8; i++)
        {
            pkzo::Geometry* ground = new pkzo::Geometry;
            ground->set_mesh(ground2_mesh);
            ground->set_material(white);
            ground->set_position(Vector3(-7.0f + (float)i * 2.0f, 3.0f, -0.2f));
            add_node(*ground);
            static_objets.push_back(ground);

            ground = new pkzo::Geometry;
            ground->set_mesh(ground2_mesh);
            ground->set_material(white);
            ground->set_position(Vector3(-7.0f + (float)i * 2.0f, 1.0f, -0.2f));
            add_node(*ground);
            static_objets.push_back(ground);

            ground = new pkzo::Geometry;
            ground->set_mesh(ground2_mesh);
            ground->set_material(white);
            ground->set_position(Vector3(-7.0f + (float)i * 2.0f, -1.0f, -0.2f));
            add_node(*ground);
            static_objets.push_back(ground);

            ground = new pkzo::Geometry;
            ground->set_mesh(ground2_mesh);
            ground->set_material(white);
            ground->set_position(Vector3(-7.0f + (float)i * 2.0f, -3.0f, -0.2f));
            add_node(*ground);
            static_objets.push_back(ground);
        }

        // cieling
        for (unsigned int i = 0; i < 8; i++)
        {
            pkzo::Geometry* ground = new pkzo::Geometry;
            ground->set_mesh(ground2_mesh);
            ground->set_material(white);
            ground->set_position(Vector3(-7.0f + (float)i * 2.0f, 3.0f, 3.0f));
            add_node(*ground);
            static_objets.push_back(ground);

            if (i == 0 || i == 7)
            {
                ground = new pkzo::Geometry;
                ground->set_mesh(ground2_mesh);
                ground->set_material(white);
                ground->set_position(Vector3(-7.0f + (float)i * 2.0f, 1.0f, 3.0f));
                add_node(*ground);
                static_objets.push_back(ground);

                ground = new pkzo::Geometry;
                ground->set_mesh(ground2_mesh);
                ground->set_material(white);
                ground->set_position(Vector3(-7.0f + (float)i * 2.0f, -1.0f, 3.0f));
                add_node(*ground);
                static_objets.push_back(ground);
            }

            ground = new pkzo::Geometry;
            ground->set_mesh(ground2_mesh);
            ground->set_material(white);
            ground->set_position(Vector3(-7.0f + (float)i * 2.0f, -3.0f, 3.0f));
            add_node(*ground);
            static_objets.push_back(ground);

            ground = new pkzo::Geometry;
            ground->set_mesh(ground2_mesh);
            ground->set_material(white);
            ground->set_position(Vector3(-7.0f + (float)i * 2.0f, 3.0f, 6.2f));
            add_node(*ground);
            static_objets.push_back(ground);

            if (i == 0 || i == 7)
            {
                ground = new pkzo::Geometry;
                ground->set_mesh(ground2_mesh);
                ground->set_material(white);
                ground->set_position(Vector3(-7.0f + (float)i * 2.0f, 1.0f, 6.2f));
                add_node(*ground);
                static_objets.push_back(ground);

                ground = new pkzo::Geometry;
                ground->set_mesh(ground2_mesh);
                ground->set_material(white);
                ground->set_position(Vector3(-7.0f + (float)i * 2.0f, -1.0f, 6.2f));
                add_node(*ground);
                static_objets.push_back(ground);
            }

            ground = new pkzo::Geometry;
            ground->set_mesh(ground2_mesh);
            ground->set_material(white);
            ground->set_position(Vector3(-7.0f + (float)i * 2.0f, -3.0f, 6.2f));
            add_node(*ground);
            static_objets.push_back(ground);
        }

        // walls x
        for (unsigned int i = 0; i < 8; i++)
        {
            pkzo::Geometry* wall = new pkzo::Geometry;
            wall->set_mesh(wall2_mesh);
            wall->set_material(white);
            wall->set_position(Vector3(-7.0f + (float)i * 2.0f, 4.1f, 0.0f));
            wall->set_orientation(Quaternion::axis_angle(90, Vector3(0, 0, 1)));
            add_node(*wall);
            static_objets.push_back(wall);

            wall = new pkzo::Geometry;
            wall->set_mesh(wall2_mesh);
            wall->set_material(white);
            wall->set_position(Vector3(-7.0f + (float)i * 2.0f, -4.1f, 0.0f));
            wall->set_orientation(Quaternion::axis_angle(90, Vector3(0, 0, 1)));
            add_node(*wall);
            static_objets.push_back(wall);

            wall = new pkzo::Geometry;
            wall->set_mesh(wall2_mesh);
            wall->set_material(white);
            wall->set_position(Vector3(-7.0f + (float)i * 2.0f, 4.1f, 3.2f));
            wall->set_orientation(Quaternion::axis_angle(90, Vector3(0, 0, 1)));
            add_node(*wall);
            static_objets.push_back(wall);

            wall = new pkzo::Geometry;
            wall->set_mesh(wall2_mesh);
            wall->set_material(white);
            wall->set_position(Vector3(-7.0f + (float)i * 2.0f, -4.1f, 3.2f));
            wall->set_orientation(Quaternion::axis_angle(90, Vector3(0, 0, 1)));
            add_node(*wall);
            static_objets.push_back(wall);
        }

        for (unsigned int i = 0; i < 4; i++)
        {
            pkzo::Geometry* wall = new pkzo::Geometry;
            wall->set_mesh(wall2_mesh);
            wall->set_material(white);
            wall->set_position(Vector3(8.1f, -3.0f + (float)i * 2.0f, 0.0f));
            add_node(*wall);
            static_objets.push_back(wall);

            wall = new pkzo::Geometry;
            wall->set_mesh(wall2_mesh);
            wall->set_material(white);
            wall->set_position(Vector3(-8.1f, -3.0f + (float)i * 2.0f, 0.0f));
            add_node(*wall);
            static_objets.push_back(wall);

            wall = new pkzo::Geometry;
            wall->set_mesh(wall2_mesh);
            wall->set_material(white);
            wall->set_position(Vector3(8.1f, -3.0f + (float)i * 2.0f, 3.2f));
            add_node(*wall);
            static_objets.push_back(wall);

            wall = new pkzo::Geometry;
            wall->set_mesh(wall2_mesh);
            wall->set_material(white);
            wall->set_position(Vector3(-8.1f, -3.0f + (float)i * 2.0f, 3.2f));
            add_node(*wall);
            static_objets.push_back(wall);
        }
    }

    AtriumScene::~AtriumScene()
    {
        for (auto obj : static_objets)
        {
            delete obj;
        }
        static_objets.clear();
    }
}