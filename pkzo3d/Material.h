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

#ifndef _PKZO_MATERIAL_H_
#define _PKZO_MATERIAL_H_

#include <memory>
#include <string>
#include <rgm/rgm.h>
#include <pkzo/defines.h>

namespace pkzo
{
    

    class Shader;

    class PKZO_EXPORT Material
    {
    public:
        
        Material();

        ~Material();

        void set_albedo(const rgm::vec3& value);

        const rgm::vec3& get_albedo() const;

        void set_roughness(float value);
        
        float get_roughness() const;

        void set_metalness(float value);

        float get_metalness() const;

        void load(const std::string& file); 

        void setup(Shader& shader) const;

    private:
        rgm::vec3  albedo;
        float roughness;
        float metalness;
    };

    PKZO_EXPORT
    std::shared_ptr<Material> load_material(const std::string& file);
}

#endif
