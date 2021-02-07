//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef _ICE_TEXTURE_H_
#define _ICE_TEXTURE_H_

#include "config.h"

#include <memory>
#include <filesystem>
#include <glm/fwd.hpp>

#include "SdlSentry.h"

struct SDL_Surface;

namespace pkzo
{
    class PKZO_EXPORT Texture
    {
    public:
        Texture(const std::filesystem::path& file);
        Texture(SDL_Surface* surface, const std::string& label = "memory") noexcept;
        Texture(const Texture&) = delete;
        ~Texture();
        Texture& operator = (const Texture&) = delete;

        //! Get the texture size.
        glm::uvec2 get_size() const noexcept;

        void upload();

        void bind(glm::uint slot);

    private:
        SdlSentry    sdl_sentry;
        SDL_Surface* surface = nullptr;
        std::string  label;
        glm::uint    gl_id = 0u;
    };
}

#endif
