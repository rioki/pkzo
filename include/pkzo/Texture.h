//
// pkzo
// 
// Copyright 2015 Sean Farrell
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 

#ifndef _PKZO_TEXTURE_H_
#define _PKZO_TEXTURE_H_

#include <string>

#include "defines.h"

struct SDL_Surface;

namespace pkzo
{
    enum ColorType
    {
        NOCOLOR,
        RGB,
        RGBA
    };

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

        void create(unsigned int w, unsigned int h, ColorType color_type, const unsigned char* data);

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

        ColorType get_color_type() const;

        const unsigned char* get_data() const;

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
