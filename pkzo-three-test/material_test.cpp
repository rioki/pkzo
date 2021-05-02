//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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
//

#include "pch.h"

TEST(Material, default_contruct)
{
    pkzo::three::Material material;
    EXPECT_TEXTURE_EQ(*pkzo::three::default_diffuse_texture(),    *material.get_diffuse());
    EXPECT_TEXTURE_EQ(*pkzo::three::default_specular_texture(),   *material.get_specular());
    EXPECT_TEXTURE_EQ(*pkzo::three::default_roughtness_texture(), *material.get_roughtness());
    EXPECT_TEXTURE_EQ(*pkzo::three::default_normal_texture(),     *material.get_normal());
    EXPECT_TEXTURE_EQ(*pkzo::three::default_emissive_texture(),   *material.get_emissive());
}

TEST(Material, load_metal_plate)
{
    pkzo::three::Material material("../../data/materials/MetalPlate.jmn");
    EXPECT_TEXTURE_EQ(pkzo::Texture("../../data/textures/texturehaven/metal_plate/metal_plate_diff_1k.jpg"),  *material.get_diffuse());
    EXPECT_TEXTURE_EQ(pkzo::Texture("../../data/textures/texturehaven/metal_plate/metal_plate_spec_1k.jpg"),  *material.get_specular());
    EXPECT_TEXTURE_EQ(pkzo::Texture("../../data/textures/texturehaven/metal_plate/metal_plate_rough_1k.jpg"), *material.get_roughtness());
    EXPECT_TEXTURE_EQ(pkzo::Texture("../../data/textures/texturehaven/metal_plate/metal_plate_Nor_1k.jpg"),   *material.get_normal());
    EXPECT_TEXTURE_EQ(*pkzo::three::default_emissive_texture(),                                               *material.get_emissive());
}

TEST(Material, load_cobble_stone)
{
    pkzo::three::Material material("../../data/materials/CobbleStone.jmn");
    EXPECT_TEXTURE_EQ(pkzo::Texture("../../data/textures/texturehaven/cobblestone_floor_04/cobblestone_floor_04_diff_1k.jpg"),  *material.get_diffuse());
    EXPECT_TEXTURE_EQ(*pkzo::three::default_specular_texture(),                                                                 *material.get_specular());
    EXPECT_TEXTURE_EQ(pkzo::Texture("../../data/textures/texturehaven/cobblestone_floor_04/cobblestone_floor_04_rough_1k.jpg"), *material.get_roughtness());
    EXPECT_TEXTURE_EQ(pkzo::Texture("../../data/textures/texturehaven/cobblestone_floor_04/cobblestone_floor_04_nor_1k.jpg"),   *material.get_normal());
    EXPECT_TEXTURE_EQ(*pkzo::three::default_emissive_texture(),                                                                 *material.get_emissive());
}
