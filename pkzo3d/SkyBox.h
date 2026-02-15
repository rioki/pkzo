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

#pragma once

#include "Node.h"

#include <pkzo/Texture.h>
#include <pkzo/CubeMap.h>

namespace pkzo3d
{
    class PKZO3D_EXPORT SkyBox : public Node
    {
    public:
        struct Specs
        {
            Node*                          parent    = nullptr;
            std::shared_ptr<pkzo::Texture> texture;
            std::shared_ptr<pkzo::CubeMap> cubemap;
        };

        SkyBox(Specs specs);
        ~SkyBox();

        std::shared_ptr<pkzo::Texture> get_texture() const;

        std::shared_ptr<pkzo::CubeMap> get_cubemap() const;
        void set_cubemap(const std::shared_ptr<pkzo::CubeMap>& value);


    private:
        std::shared_ptr<pkzo::Texture> texture;
        std::shared_ptr<pkzo::CubeMap> cubemap;
    };
}
