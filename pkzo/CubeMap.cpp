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

#include "CubeMap.h"

#include <fstream>
#include <GL/glew.h>

namespace pkzo
{
    CubeMap::CubeMap()
    : glid(0) {}

    CubeMap::~CubeMap()
    {
        release();
    }

    void CubeMap::load(const std::string& xp, const std::string& xn, 
                       const std::string& yp, const std::string& yn,
                       const std::string& zp, const std::string& zn)
    {
        xpos.load(xp);
        xneg.load(xn);
        ypos.load(yp);
        yneg.load(yn);
        zpos.load(zp);
        zneg.load(zn);
    }


    void CubeMap::bind(unsigned int slot) const
    {
        if (glid == 0)
        {
            upload();
        }
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, glid);
    }

    void CubeMap::upload() const
    {
        glGenTextures(1, &glid);
        glBindTexture(GL_TEXTURE_CUBE_MAP, glid);

        // TODO mipmap
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        int mode = 0;
        switch (xpos.get_color_type())
        {
        case RGB:
            mode = GL_RGB;
            break;
        case RGBA:
            mode = GL_RGBA;
            break;
        default:
            throw std::logic_error("Unknown pixel format.");
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, mode, xpos.get_width(), xpos.get_height(), 0, mode, GL_UNSIGNED_BYTE, xpos.get_data());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, mode, xneg.get_width(), xneg.get_height(), 0, mode, GL_UNSIGNED_BYTE, xneg.get_data());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, mode, ypos.get_width(), ypos.get_height(), 0, mode, GL_UNSIGNED_BYTE, ypos.get_data());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, mode, yneg.get_width(), yneg.get_height(), 0, mode, GL_UNSIGNED_BYTE, yneg.get_data());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, mode, zpos.get_width(), zpos.get_height(), 0, mode, GL_UNSIGNED_BYTE, zpos.get_data());
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, mode, zneg.get_width(), zneg.get_height(), 0, mode, GL_UNSIGNED_BYTE, zneg.get_data());
    }

    void CubeMap::release() const
    {
        if (glid != 0)
        {
            glDeleteTextures(1, &glid);
            glid = 0;
        }
    }
}