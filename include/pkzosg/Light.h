
#ifndef _PKZOSG_LIGHT_H_
#define _PKZOSG_LIGHT_H_

#include "SceneNode.h"

#include <pkzo/Color.h>

namespace pkzo
{
    class PKZOSG_EXPORT Light : public SceneNode
    {
    public:
        
        Light();

        ~Light();

        void set_color(const Color& value);

        const Color& get_color() const;

    private:
        Color color;
    };
}

#endif
