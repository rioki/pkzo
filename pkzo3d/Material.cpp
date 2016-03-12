/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "Material.h"

#include <fstream>
#include <rjson.h>
#include <pkzo/Shader.h>

namespace pkzo
{
    Material::Material()
    : albedo(0.5), roughness(0.5), metalness(0.0) {}

    Material::~Material() {}

    void Material::set_albedo(const vec3& value)
    {
        albedo = value;
    }

    const vec3& Material::get_albedo() const
    {
        return albedo;
    }

    void Material::set_roughness(float value)
    {
        roughness = value;
    }
        
    float Material::get_roughness() const
    {
        return roughness;
    }

    void Material::set_metalness(float value)
    {
        metalness = value;
    }

    float Material::get_metalness() const
    {
        return metalness;
    }

    // http://stackoverflow.com/questions/16388510/evaluate-a-string-with-a-switch-in-c
    constexpr unsigned int str2int(const char* str, int h = 0)
    {
        return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
    }

    void Material::load(const std::string& file)
    {
        std::ifstream in(file);
        if (! in.is_open())
        {
            throw std::runtime_error("Failed to open material "+ file + " for reading.");
        }

        rjson::Object jmat;

        in >> jmat;

        for (auto val : jmat)
        {
            switch (str2int(val.first.c_str()))
            {
                case str2int("albedo"):
                {
                    rjson::Array jalbedo = val.second;
                    if (jalbedo.size() == 3)
                    {
                        throw std::runtime_error("Albedo must have 3 values.");
                    }

                    albedo[0] = jalbedo[0];
                    albedo[1] = jalbedo[1];
                    albedo[2] = jalbedo[2];
                    break;
                }
                case str2int("roughness"):
                {
                    roughness = val.second;
                    break;
                }
                case str2int("metalness"):
                {
                    metalness = val.second;
                    break;
                }
                default:
                {
                    throw std::runtime_error("Unknown material property " + val.first + ".");
                }
            }
        }
    }

    void Material::setup(Shader& shader) const
    {
        shader.set_uniform("uMaterialAlbedo", albedo);
    }

    std::shared_ptr<Material> load_material(const std::string& file)
    {
        std::shared_ptr<Material> material(new Material);
        material->load(file);
        return material;
    }
}
