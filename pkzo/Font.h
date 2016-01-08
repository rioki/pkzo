
#ifndef _PKZO_FONT_H_
#define _PKZO_FONT_H_

#include <string>
#include <tuple>

#include "defines.h"
#include "Texture.h"

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;

namespace pkzo
{
    class PKZO_EXPORT Font
    {
    public:
        Font();

        Font(const Font&) = delete;

        ~Font();

        const Font& operator = (const Font&) = delete;

        void load(const std::string& file, unsigned int size);

        std::tuple<unsigned int, unsigned int> estimate(const std::string& text) const;

        Texture render(const std::string& text) const;

    private:
        TTF_Font* font; 
    };
}

#endif
