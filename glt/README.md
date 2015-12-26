OpenGL Transformation Library
=============================

There are many cases where you need compute a simple projection or movel-view
matrix, but you don't need a full linear algebra library. glt was built
for exactly this case. It emulates the OpenGL 1.0 transformation functions, 
but work on float arrays, that can then be passed to GLSL shaders.

Functions
---------

glt provides the following functions:

    void gltLoadIdentity(float* matrix);

    void gltMultMatrix(float* matrix, float* other);

    void gltOrtho(float* matrix, float left, float right, float bottom, float top, float near, float far);

    void gltOrtho2D(float* matrix, float left, float right, float bottom, float top);

    void gltFrustum(float* matrix, float left, float right, float bottom, float top, float near, float far);

    void gltPerspective(float* matrix, float fovy, float aspect, float near, float far);

    void gltLookAt(float* matrix, float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);

    void gltTranslate(float* matrix, float x, float y, float z);

    void gltRotate(float* matrix, float angle, float x, float y, float z);

    void gltScale(float* matrix, float x, float y, float z);

And they work similar to their gl and glu counterparts. 
(Except that translate, rotate and scale do not have variants, only "3f".)

Example
-------

Using the library is quite simple and straight forward. For example if you 
want to compute a perspective projection matrix:

    float projectionMatrix[16];
    
    // width and height from window / screen size
    float aspect = (float)width / (float)height;
    
    gltPerspective(projectionMatrix, 45.0f, aspect, 0.1f, 1000.0f);
    
And a view matrix with LookAt works as well:

    float modelViewMatrix[16];
    
    glLoadIdentity(modelViewMatrix);
    glLookAt(modelViewMatrix, -10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    
If you want to push and pop, you need to implement that yourself, but to add
a model bit to the view:

    glTranslate(modelViewMatrix, 0.0f, 5.0f, 2.0f);
    glRotate(modelViewMatrix, 30.0f, 0.0f, 0.0f);
    
Now you only need to pass that array to a uniform variable in your shader.

License
-------

    Copyright (c) 2015 Sean Farrell

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
