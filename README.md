pkzo
====

About
-----

I kept writing the similar objects over and over, so I decided to distill them 
into one consistent library. The libary provides all you need to quickly get up
to speed with OpenGL. 

pkzo provides the following features:

* a window with OpenGL 4.0 rendering context
* a mouse and keyboard abstraction
* a GLSL shader handler
* a triangle mesh class, that load PLY files
* a texture class, that loads JPEG, PNG, TIFF and WebP images
* loading TTF fonts and rendering them to 2D texture

pkzoui provides the following features:

* 2D rendering infrastructure
* rendering simple rectangle
* rendering text.

Open Issues
-----------

I will extent the library as required for my projects or on request. The 
following things I still have lying around and can quickly integrate.

* loading meshes from OBJ and STL 
* computing normals
* computing tangents

Portability
-----------

The code itself should compile on any system that supports C++11 and libSDL.
I just can't be bothered to maintain multiple build definitions and 
all portable build definitions are either high maintenance or moronic.

(Before you suggest CMake, it's one of the moronic ones.)

License
-------

The library pkzo, contained in the folder src is covered by the following 
license:

    The MIT License (MIT)

    Copyright 2015 Sean Farrell

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
    
The example code (examples/**/*.(cpp|h|glsl) is provided by me as is under public 
domain, unless otherwise noted in the file.

The Utah Teapot (examples/teapot/Teapot.ply) was create by Martin Newell in 1975
and made public by him.

The DejaVu fonts are copyright Bitstream. DejaVu changes are in public 
domain. Glyphs imported from Arev fonts are copyright Tavmjong Bah. 
See examples/assets/fonts/DejaVu-LICENSE.txt for details.

The sky textures (examples/assets/textures/Morning_*.jpg and 
examples/assets/textures/CloudyAfternoon_*.jpg and) are from 
"Fully Immersive 360° Sky Backgrounds" package by Johannes Schloerb. 
Redistribution is limited to the pkzo examples. But you can get your
own license under http://www.turbosquid.com/FullPreview/Index.cfm/ID/240748.

The other textures (examples/assets/textures/*) where created by me 
(Copyright 2014 Sean Farrell) and are licensed under 
[Creative Commons Attribution 3.0 License](http://creativecommons.org/licenses/by/3.0).

The icons (examples/assets/icons/*) are from [Icons8](https://icons8.com) and
are shared under the Terms of the 
[Creative Commons Attribution-NoDerivs 3.0 Unported](https://creativecommons.org/licenses/by-nd/3.0).




