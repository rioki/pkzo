
#ifndef _PKZOSG_MATERIAL_H_
#define _PKZOSG_MATERIAL_H_

#include "defines.h"

#include <memory>
#include <pkzo/Color.h>

namespace pkzo
{
    class Shader;
    class Texture;

    class PKZOSG_EXPORT Material
    {
    public:
        
        Material();

        Material(const Material&) = delete;

        ~Material();

        const Material& operator = (const Material&) = delete;

        void set_color(const Color& value);

        const Color& get_color() const;

        void set_texture(std::shared_ptr<pkzo::Texture> value);

        std::shared_ptr<pkzo::Texture> get_texture() const;

        void setup(Shader& shader) const;

    private:
        Color                          color;
        std::shared_ptr<pkzo::Texture> texture;
    };
};

#endif

