
#ifndef _PKZO_TEXTURE_H_
#define _PKZO_TEXTURE_H_

#include <string>

#include "defines.h"

struct SDL_Surface;

namespace pkzo
{
    class PKZO_EXPORT Texture
    {
    public:
        
        Texture();
        
        Texture(const Texture&) = delete;    

        ~Texture();

        const Texture& operator = (const Texture&) = delete;

        void load(const std::string& file);

        unsigned int get_width() const;

        unsigned int get_height() const;

        void bind(unsigned int slot) const;

        void upload() const;

        void release() const;

    private:
        SDL_Surface* surface;
        mutable unsigned int glid;
    };
}

#endif
