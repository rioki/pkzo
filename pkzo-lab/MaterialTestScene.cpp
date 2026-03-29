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

#include "MaterialTestScene.h"

#include "env.h"

namespace lab
{
    MaterialTestScene::MaterialTestScene()
    {
        constexpr auto MATERIAL_PER_ROW = 5u;

        auto base = get_asset_folder();

        set_gravity(glm::vec3(0.0f, 0.0f, -9.81f));

        add<pkzo::SkyBox>({
            .texture = pkzo::Texture::load_file({
                .file  = base / "polyhaven/skies/qwantani_dusk_2_puresky_1k.exr",
                .clamp = pkzo::Clamp::CLAMP_VERTICAL
            })
        });

        // TODO get light dir and color from env
        add<pkzo::DirectionalLight>({
            .transform    = pkzo::lookat(glm::vec3(0.4f, 0.5f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
            .color     = glm::vec3(0.55, 0.58, 0.65)
        });

        auto materials = std::vector<std::shared_ptr<pkzo::Material>>{};

        auto values = std::vector<float>{1.0, 0.75, 0.5, 0.25, 0.0};
        for (auto i = 0u; i < 5; i++)
        {
            materials.push_back(pkzo::Material::create({
                .base_color_factor = glm::vec3(0.7f),
                .roughness_factor  = values[i],
                .metallic_factor   = 0.0f
            }));
        }

        for (auto i = 0u; i < 5; i++)
        {
            materials.push_back(pkzo::Material::create({
                .base_color_factor = glm::vec3(0.7f),
                .roughness_factor  = values[i],
                .metallic_factor   = 1.0f
            }));
        }

        // wood floors
        materials.push_back(pkzo::Material::load(base / "polyhaven/materials/herringbone_parquet.yml"));
        materials.push_back(pkzo::Material::load(base / "polyhaven/materials/laminate_floor_02.yml"));
        materials.push_back(pkzo::Material::load(base / "polyhaven/materials/plank_flooring_04.yml"));
        materials.push_back(pkzo::Material::load(base / "polyhaven/materials/wood_floor_deck.yml"));
        materials.push_back(pkzo::Material::load(base / "polyhaven/materials/wood_floor_worn.yml"));

        // stone floors
        materials.push_back(pkzo::Material::load(base / "polyhaven/materials/brick_pavement_03.yml"));
        materials.push_back(pkzo::Material::load(base / "polyhaven/materials/cracked_concrete.yml"));
        materials.push_back(pkzo::Material::load(base / "polyhaven/materials/gravel_concrete_03.yml"));
        materials.push_back(pkzo::Material::load(base / "polyhaven/materials/hangar_concrete.yml"));
        materials.push_back(pkzo::Material::load(base / "polyhaven/materials/hexagonal_concrete_paving.yml"));

        auto start = glm::vec3(0.0f);
        auto step  = glm::vec3(1.0f, 1.0f, 1.5f);
        for (auto i = 0u; i < materials.size(); i++)
        {
            auto column = i % MATERIAL_PER_ROW;
            auto row    = i / MATERIAL_PER_ROW;

            add<pkzo::BoxGeometry>({
                .transform     = pkzo::position(start + glm::vec3(column * step.x, row * step.y, 0.0f * step.z)),
                .collidable    = false,
                .size          = glm::vec3(0.5f),
                .material      = materials[i]
            });

            add<pkzo::SphereGeometry>({
                .transform     = pkzo::position(start + glm::vec3(column * step.x, row * step.y, 1.0f * step.z)),
                .collidable    = false,
                .diameter      = 0.5f,
                .material      = materials[i]
            });
        }
    }
}