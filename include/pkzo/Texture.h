
#ifndef _PKZO_TEXTURE_H_
#define _PKZO_TEXTURE_H_

#include <string>

#include "defines.h"

struct SDL_Surface;

namespace pkzo
{
    /**
     * Texture
     **/    
    class PKZO_EXPORT Texture
    {
    public:
        
        /**
         * Create a Texture
         **/
        Texture();
        
        Texture(const Texture&) = delete;    

        /**
         * Destroy Texture
         **/
        ~Texture();

        const Texture& operator = (const Texture&) = delete;

        /**
         * Load a Texture from File
         *
         * This function loads images in the formats JPEG, PNG, TIFF, and WebP.
         *
         * @param file the file to load from
         **/
        void load(const std::string& file);

        /**
         * Get the Image Width
         *
         * @returns the image width in pixels
         **/
        unsigned int get_width() const;

        /**
         * Get the Image Height
         *
         * @returns the image height in pixels
         **/
        unsigned int get_height() const;

        /**
         * Bind the Texture
         *
         * This function will bind the texture to a specific texture slot.
         * 
         * @param slot the textrue slot to bind to
         *
         * @warning This function can only be called with a valid and active OpenGL context.
         **/
        void bind(unsigned int slot) const;

        /**
         * Upload Texture to Video Memeory
         *
         * @warning This function can only be called with a valid and active OpenGL context.
         **/
        void upload() const;

        /**
         * Release Texture from Video Memeory
         *
         * @warning This function can only be called with a valid and active OpenGL context.
         **/
        void release() const;

    private:
        SDL_Surface* surface;
        mutable unsigned int glid;
    };
}

#endif
