// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "PhysicsTestScene.h"

#include "env.h"
#include "Prop.h"

namespace lab
{
    PhysicsTestScene::PhysicsTestScene()
    {
        auto base = get_asset_folder();

        set_gravity(glm::vec3(0.0f, 0.0f, -9.81f));

        add<pkzo::SkyBox>({
            .texture = pkzo::Texture::load_file({
                .file  = base / "polyhaven/skies/qwantani_dusk_2_puresky_1k.exr",
                .clamp = pkzo::Clamp::CLAMP_VERTICAL
            })
        });

        add<pkzo::BoxGeometry>({
            .transform     = pkzo::position(0.0f, 0.0f, -0.5f),
            .size          = glm::vec3(100.0f, 100.0f, 1.0f),
            .texture_scale = glm::vec3(100.0f, 100.0f, 1.0f),
            .material      = pkzo::Material::load(base / "polyhaven/materials/gravel_concrete_03.yml")
        });

        add<Prop>({
            .transform = pkzo::position(0.0f, 0.2f, 1.0f),
            .model     = "polyhaven/models/barrel_01_2k/barrel_01_2k.gltf",
            .collision = Prop::Collision::BOUNDING_CYLINER_Z
        });

        add<Prop>({
            .transform = pkzo::position(0.2f, 0.0f, 2.0f),
            .model     = "polyhaven/models/barrel_01_2k/barrel_01_2k.gltf",
            .collision = Prop::Collision::BOUNDING_CYLINER_Z
        });

        add<Prop>({
            .transform = pkzo::position(0.0f, -0.2f, 3.0f),
            .model     = "polyhaven/models/barrel_01_2k/barrel_01_2k.gltf",
            .collision = Prop::Collision::BOUNDING_CYLINER_Z
        });

        add<Prop>({
            .transform = pkzo::position(0.0f, 0.0f, 4.0f),
            .model     = "polyhaven/models/barrel_01_2k/barrel_01_2k.gltf",
            .collision = Prop::Collision::BOUNDING_CYLINER_Z
        });

        constexpr auto ball_position = glm::vec3(0.0f, 0.0f, 5.0f);
        constexpr auto ball_count    = glm::uvec3(3u);
        constexpr auto ball_spacing  = glm::vec3(0.3f);
        constexpr auto ball_start    = ball_position - ball_spacing * (glm::vec3(ball_count) / 2.0f);
        for (auto i = 0u; i < ball_count.x; i++)
        {
            for (auto j = 0u; j < ball_count.y; j++)
            {
                for (auto k = 0u; k < ball_count.z; k++)
                {
                    add<Prop>({
                        .transform = pkzo::position(ball_start + glm::vec3(i, j, k) * ball_spacing),
                        .model     = "polyhaven/models/baseball_01_2k/baseball_01_2k.gltf",
                        .mass      = 0.150f,
                        .collision = Prop::Collision::BOUNDING_SPHERE
                    });
                }
            }
        }

        enable_physics_debug();
    }
}
