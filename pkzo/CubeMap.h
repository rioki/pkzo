/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

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
        
        void load(const std::string& xp, const std::string& xn, 
                  const std::string& yp, const std::string& yn,
                  const std::string& zp, const std::string& zn);

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

    PKZO_EXPORT
    std::shared_ptr<CubeMap> load_cubemap(const std::string& xp, const std::string& xn, 
                                          const std::string& yp, const std::string& yn,
                                          const std::string& zp, const std::string& zn);
}

#endif
