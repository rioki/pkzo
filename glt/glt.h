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

#ifndef _GLT_H_
#define _GLT_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load Identity Matrix
 *
 * This function will load the indetity matix into @a m.
 * 
 * @param matrix the matrix
 **/
void gltLoadIdentity(float* matrix);

/**
 * Multiply a Matrices onto an Other
 *
 * @param matrix the matrix
 * @param other  the other matrix
 **/
void gltMultMatrix(float* matrix, float* other);

/**
 * Compute Orthographic Projection Matrix
 *
 * This function computes a orthographic projection matrix.
 *
 * @param matrix the matrix
 * @param left   the left edge of the viewport
 * @param right  the right edge of the viewport
 * @param bottom the bottom edge of the viewport
 * @param top    the top edge of the viewport
 * @param near   the near clipping plane
 * @param faar   the far clipping plane
 **/
void gltOrtho(float* matrix, float left, float right, float bottom, float top, float near, float far);

/**
 * Compute 2D Orthographic Projection Matrix
 *
 * This function computes a projection matrix with the near clipping plane at -1 and 
 * the far clipping plane at 1.
 *
 * @param matrix the matrix
 * @param left   the left edge of the viewport
 * @param right  the right edge of the viewport
 * @param bottom the bottom edge of the viewport
 * @param top    the top edge of the viewport
 **/
void gltOrtho2D(float* matrix, float left, float right, float bottom, float top);

/**
 * Compute Frustum Projection Matrix
 *
 * @param matrix the matrix
 * @param left   the left clipping plane
 * @param right  the right clipping plane
 * @param bottom the bottom clipping plane
 * @param top    the top clipping plane
 * @param near   the near clipping plane
 * @param faar   the far clipping plane
 **/
void gltFrustum(float* matrix, float left, float right, float bottom, float top, float near, float far);

/**
 * Compute Perspective Projection Matrix
 *
 * @param matrix the matrix
 * @param fovy   the field of view along the y axis
 * @param aspect the aspect ratio
 * @param near   the near clipping plane
 * @param faar   the far clipping plane
 **/
void gltPerspective(float* matrix, float fovy, float aspect, float near, float far);

void gltLookAt(float* matrix, float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);

/**
 * Add Translation to Matrix
 *
 * This function adds a transation to a model-view matrix.
 *
 * @param matrix the matrix
 * @param x      the x translation
 * @param y      the y translation
 * @param z      the z translation
 **/
void gltTranslate(float* matrix, float x, float y, float z);

/**
 * Add Rotation to Matrix
 *
 * This function adds a ration to a movel-view matrix.
 * 
 * @param matrix the matrix
 * @param angle  the rotation angle
 * @param x      the x component of the axis
 * @param y      the y component of the axis
 * @param z      the z component of the axis
 **/
void gltRotate(float* matrix, float angle, float x, float y, float z);

/**
* Add Scale to Matrix
*
* This function adds a scale to a model-view matrix.
*
* @param matrix the matrix
* @param x      the x scale
* @param y      the y scale
* @param z      the z scale
**/
void gltScale(float* matrix, float x, float y, float z);

#ifdef __cplusplus
}
#endif

#endif


