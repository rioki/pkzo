
#include "CubeMap.h"

#include <fstream>
#include <rjson.h>
#include <GL/glew.h>

#include "path.h"
#include "Compose.h"

namespace pkzo
{
    CubeMap::CubeMap()
    : glid(0) {}

    CubeMap::~CubeMap()
    {
        release();
    }

    void CubeMap::load(const std::string& file)
    {
        std::ifstream in(file);
        if (! in.is_open())
        {
            throw std::runtime_error(compose("Failed to open %0 for reading.", file));
        }
        
        std::string dir = path::dirname(file);

        rjson::Object jcm;
        in >> jcm;

        xpos.load(path::join(dir, jcm["xpos"]));
        xneg.load(path::join(dir, jcm["xneg"]));
        ypos.load(path::join(dir, jcm["ypos"]));
        yneg.load(path::join(dir, jcm["yneg"]));
        zpos.load(path::join(dir, jcm["zpos"]));
        zneg.load(path::join(dir, jcm["zneg"]));
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
