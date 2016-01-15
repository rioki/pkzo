
#ifndef _PKZO_CUBE_MAP_H_
#define _PKZO_CUBE_MAP_H_

#include "defines.h"

#include "Texture.h"

namespace pkzo
{

    class PKZO_EXPORT CubeMap
    {
    public:
        
        CubeMap();

        CubeMap(const CubeMap&) = delete;

        ~CubeMap();

        const CubeMap& operator = (const CubeMap&) = delete;

        void load(const std::string& file);

        void bind(unsigned int slot) const;

        void upload() const;

        void release() const;

    private:
        mutable unsigned int glid;
        Texture xpos;
        Texture xneg;
        Texture ypos;
        Texture yneg;
        Texture zpos;
        Texture zneg;

    };
}

#endif