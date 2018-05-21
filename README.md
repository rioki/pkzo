# pkzo

## About

I kept writing the similar objects over and over, so I decided to distill them 
into one consistent library. The libary provides all you need to quickly get 
up to speed with OpenGL.

pkzo provides the following features:

* window with OpenGL 4.0 rendering context
* mouse and keyboard abstraction
* triangle mesh class, that load PLY and OBJ files
* texture class, that loads JPEG, PNG, TIFF and WebP images
* loading TTF fonts and rendering them to 2D texture

# Portability

The code itself should compile on any system that supports C++11 and libSDL. 
I just can't be bothered to maintain multiple build definitions and all 
portable build definitions are either high maintenance or moronic.

(Before you suggest CMake, it's one of the moronic ones.)

## License

    Copyright 2018 Sean Farrell <sean.farrell@rioki.org>

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
