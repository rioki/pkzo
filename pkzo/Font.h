// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_FONT_H_
#define _PKZO_FONT_H_

#include <memory>
#include <string>
#include <filesystem>
#include <glm/glm.hpp>

#include "defines.h"
#include "SdlSentry.h"

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;

namespace fs = std::filesystem;

namespace pkzo
{
    class Image;

    class PKZO_EXPORT Font
    {
    public:

        Font(const fs::path& file, unsigned int size);

        Font(const Font&) = delete;

        ~Font();

        const Font& operator = (const Font&) = delete;

        glm::uvec2 estimate(const std::string& text) const;

        std::shared_ptr<Image> render(const std::string& text) const;

    private:
        SDLSentry sdl_sentry;

        TTF_Font* font; 
    };
}

#endif
