pkzo or 'a Libary with Low Level OpenGL Objects'
================================================

About
-----

I kept writing the similar objects over and over, so I decided to distill them 
into one consistent library. The libary provides all you need to quickly get up
to speed with OpenGL. 

pkzo provides the following primitives:

* a window with OpenGL 4.0 rendering context
* a mouse and keyboard abstraction
* a GLSL shader handler
* a triangle mesh class, that load PLY files
* a texture class, that loads JPEG, PNG, TIFF and WebP images

Open Issues
-----------

I will extent the library as required for my projects or on request. The 
following things I sill have lying around and can quickly integrate.

* loading meshes from OBJ and STL 
* loading TTF fonts and rendering them to 2D texture
* computing normals
* computing tangents

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
    
The example code (examples/**/*.(cpp|h|glsl) is provided as is under public 
domain, unless otherwise noted in the file.

The Utah Teapot (examples/teapot/Teapot.ply) was create by Martin Newell in 1975
and made public by him.

The textures (examples/**/*.png) where created by me 
(Copyright 2014 Sean Farrell) and are licensed under 
[Creative Commons Attribution 3.0 License](http://creativecommons.org/licenses/by/3.0).




