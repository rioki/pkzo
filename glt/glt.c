/*

  OpenGL Transformation Library

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

*/

#include "glt.h"

#define _USE_MATH_DEFINES
#include <memory.h>
#include <math.h>

const size_t m4size = sizeof(float) * 16; 

float radians(float degrees) 
{
    return degrees * ((float)M_PI / 180.0f);
};

float degrees(float radians) 
{
    return radians * (180.0f / (float)M_PI);
};

void gltLoadIdentity(float* m)
{
    memset(m, 0, m4size);
    m[0] = m[5] = m[10] = m[15] = 1.0f;
}

void gltMultMatrix(float* m, float* o)
{
    unsigned int i, j, k;
    float r[16];
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            float v = 0;
            for (k = 0; k < 4; k++) {
                v = v + m[i*4 + k] * o[k*4 + j];
            }
            r[i*4 + j] = v;
        }
    }

    memcpy(m, r, m4size);
}

void gltOrtho(float* m, float left, float right, float bottom, float top, float near, float far)
{
    float rl = right - left;
    float tb = top   - bottom;
    float fn = far   - near;

    m[0]  = 2 / rl;
    m[1]  = 0;
    m[2]  = 0;
    m[3]  = 0;
    m[4]  = 0;
    m[5]  = 2 / tb;
    m[6]  = 0;
    m[7]  = 0;
    m[8]  = 0;
    m[9]  = 0;
    m[10] = -2 / fn;
    m[11] = 0;
    m[12] = -(left + right) / rl;
    m[13] = -(top + bottom) / tb;
    m[14] = -(far + near) / fn;
    m[15] = 1;
}

void gltOrtho2D(float* m, float left, float right, float bottom, float top)
{
    gltOrtho(m, left, right, bottom, top, -1.0f, 1.0f);
}

void gltFrustum(float* m, float left, float right, float bottom, float top, float near, float far)
{
    float t1 = 2 * near;
    float t2 = right - left;
    float t3 = top   - bottom;
    float t4 = far   - near;

    m[0]  = t1 / t2; 
    m[1]  = 0;       
    m[2]  = 0;       
    m[3]  = 0;       
    m[4]  = 0;       
    m[5]  = t1 / t3; 
    m[6]  = 0;       
    m[7]  = 0;       
    m[8]  = (right + left) / t2;   
    m[9]  = (top + bottom) / t3;   
    m[10] = (-far - near) / t4; 
    m[11] = -1;                   
    m[12] = 0;
    m[13] = 0;
    m[14] = (-t1 * far) / t4;
    m[15] = 0;
}

void gltPerspective(float* m, float fovy, float aspect, float near, float far)
{
    float ymax = near * tanf(radians(fovy));
    float xmax = ymax * aspect;
    gltFrustum(m, -xmax, xmax, -ymax, ymax, near, far);
}

void normalize(float* v)
{
    float l = sqrtf(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    v[0] *= 1.0f / l;
    v[1] *= 1.0f / l;
    v[2] *= 1.0f / l;
}

void cross(float* r, float* a, float* b)
{
    r[0] = (a[1] * b[2]) - (a[2] * b[1]);
    r[1] = (a[2] * b[0]) - (a[0] * b[2]);
    r[2] = (a[0] * b[1]) - (a[1] * b[0]);
}

void gltLookAt(float* matrix, float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
    float forward[3], side[3], up[3];
    float matrix2[16];
    
    up[0] = upx;
    up[1] = upy;
    up[2] = upz;
    normalize(up);

    forward[0] = centerx - eyex;
    forward[1] = centery - eyey;
    forward[2] = centerz - eyez;    
    normalize(forward);

    cross(side, forward, up);
    normalize(side);

    cross(up, side, forward);
    
    matrix2[0] = side[0];
    matrix2[4] = side[1];
    matrix2[8] = side[2];
    matrix2[12] = 0.0;
    
    matrix2[1] = up[0];
    matrix2[5] = up[1];
    matrix2[9] = up[2];
    matrix2[13] = 0.0;
    
    matrix2[2] = -forward[0];
    matrix2[6] = -forward[1];
    matrix2[10] = -forward[2];
    matrix2[14] = 0.0;
    
    matrix2[3] = matrix2[7] = matrix2[11] = 0.0;
    matrix2[15] = 1.0;
    
    gltMultMatrix(matrix, matrix2);
    gltTranslate(matrix, -eyex, -eyey, -eyez);
}

void gltTranslate(float* m, float x, float y, float z)
{
    m[12] = m[0] * x + m[4] * y + m[8] * z + m[12];
    m[13] = m[1] * x + m[5] * y + m[9] * z + m[13];
    m[14] = m[2] * x + m[6] * y + m[10] * z + m[14];
    m[15] = m[3] * x + m[7] * y + m[11] * z + m[15];
}

void gltRotate(float* m, float angle, float x, float y, float z)
{
    float a = radians(angle);
    float c = cosf(a);
    float s = sinf(a);

    float l = sqrtf(x * x + y * y + z * z);
    float nx = x / l;
    float ny = y / l;
    float nz = z / l;

    float t0 = nx * (1 - c);
    float t1 = ny * (1 - c);
    float t2 = nz * (1 - c);

    float xt = m[12];
    float yt = m[13];
    float zt = m[14];
    float mt = m[15];

    float d[16];
    gltLoadIdentity(d);

    d[0] = c + t0 * nx;
    d[1] = 0 + t0 * ny + s * nz;
    d[2] = 0 + t0 * nz - s * ny;

    d[4] = 0 + t1 * nx - s * nz;
    d[5] = c + t1 * ny;
    d[6] = 0 + t1 * nz + s * nx;

    d[8] = 0 + t2 * nx + s * ny;
    d[9] = 0 + t2 * ny - s * nx;
    d[10] = c + t2 * nz;

    gltMultMatrix(m, d);

    m[12] = xt;
    m[13] = yt;
    m[14] = zt;    
    m[15] = mt;
}


void gltScale(float* m, float x, float y, float z)
{
    m[0]  = m[0]  * x;
    m[1]  = m[1]  * x;
    m[2]  = m[2]  * x;
    m[3]  = m[3]  * x;

    m[4]  = m[4]  * y;
    m[5]  = m[5]  * y;
    m[6]  = m[6]  * y;
    m[7]  = m[7]  * y;

    m[8]  = m[8]  * z;
    m[9]  = m[9]  * z;
    m[10] = m[10] * z;
    m[11] = m[11] * z;

    m[12] = m[12];
    m[13] = m[13];
    m[14] = m[14];
    m[15] = m[15];
}

