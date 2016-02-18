
#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>
#include <algorithm>

namespace pkzo
{
    Texture::Texture()
    : surface(nullptr), glid(0) {}

    Texture::Texture(Texture&& other)
    : surface(nullptr), glid(0)
    {
        std::swap(surface, other.surface);
        std::swap(glid, other.glid);
    }

    Texture::~Texture()
    {
        if (surface != nullptr)
        {
            release();
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }

    const Texture& Texture::operator = (Texture&& other)
    {
        std::swap(surface, other.surface);
        std::swap(glid, other.glid);

        return *this;
    }

    void Texture::load(const std::string& file)
    {
        if (surface != nullptr)
        {
            release();
            SDL_FreeSurface(surface);
            surface = nullptr;
        }

        surface = IMG_Load(file.c_str());
        if (surface == nullptr)
        {
            throw std::runtime_error(IMG_GetError());
        }
    }

    void Texture::create(unsigned int w, unsigned int h, ColorType color_type, const unsigned char* data)
    {
        if (color_type == NOCOLOR)
        {
            throw std::invalid_argument("Texture::create: color_type == NOCOLOR");
        }
        if (data == NULL)
        {
            throw std::invalid_argument("Texture::create: data == NULL");
        }

        if (surface != nullptr)
        {
            release();
            SDL_FreeSurface(surface);
            surface = nullptr;
        }

        int bpp   = color_type == RGB ? 3 : 4;
        int depth = color_type == RGB ? 24 : 32;
        int pitch = w * bpp;
        #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        int rmask = 0xff000000;
        int gmask = 0x00ff0000;
        int bmask = 0x0000ff00;
        int amask = 0x000000ff;
        #else
        int rmask = 0x000000ff;
        int gmask = 0x0000ff00;
        int bmask = 0x00ff0000;
        int amask = 0xff000000;
        #endif

        void* cdata = malloc(w*h*bpp);
        memcpy(cdata, data, w*h*bpp);

        surface = SDL_CreateRGBSurfaceFrom(cdata, w, h, depth, pitch, rmask, gmask, bmask, amask);
    }

    unsigned int Texture::get_width() const
    {
        if (surface)
        {
            return surface->w;
        }
        else
        {
            return 0;
        }
    }


    unsigned int Texture::get_height() const
    {
        if (surface)
        {
            return surface->h;
        }
        else
        {
            return 0;
        }
    }

    rgm::ivec2 Texture::get_size() const
    {
        if (surface)
        {
            return rgm::ivec2(surface->w, surface->h);
        }
        else
        {
            return rgm::ivec2(0, 0);
        }        
    }

    ColorType Texture::get_color_type() const
    {
        if (surface)
        {
            switch (surface->format->BytesPerPixel)
            {
            case 3:
                return RGB;
            case 4:
                return RGBA;
            default:
                throw std::logic_error("Unknown pixel format.");
            }
        }
        else
        {
            return NOCOLOR;
        }
    }

    const unsigned char* Texture::get_data() const
    {
        if (surface)
        {
            return reinterpret_cast<const unsigned char*>(surface->pixels);
        }
        else
        {
            return 0;
        }
    }

    void Texture::bind(unsigned int slot) const
    {
        if (surface != nullptr)
        {
            if (glid == 0)
            {
                upload();
            }
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, glid);
        }
        else
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, glid);
        }
    }

    void Texture::upload() const
    {
        glGenTextures(1, &glid);
        glBindTexture(GL_TEXTURE_2D, glid);

        // TODO mipmap
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int mode = 0;
        switch (surface->format->BytesPerPixel)
        {
        case 3:
            mode = GL_RGB;
            break;
        case 4:
            mode = GL_RGBA;
            break;
        default:
            throw std::logic_error("Unknown pixel format.");
        }

        glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    }

    void Texture::release() const
    {
        if (glid != 0)
        {
            glDeleteTextures(1, &glid);
            glid = 0;
        }
    }

    void Texture::set_surface(SDL_Surface* value)
    {
        if (surface != nullptr)
        {
            release();
            SDL_FreeSurface(surface);
        }

        surface = value;
    }
}
