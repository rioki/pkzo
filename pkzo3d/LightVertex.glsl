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

#version 400

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

uniform rgm::vec3 uLightDirection;
uniform rgm::vec3 uLightPosition;

layout(location = 0) in rgm::vec4 aVertex;
layout(location = 1) in rgm::vec3 aNormal;
layout(location = 2) in rgm::vec2 aTexCoord;
layout(location = 3) in rgm::vec2 aTangent;
layout(location = 4) in rgm::vec3 aColor;

out rgm::vec3 vPosition;
out rgm::vec3 vNormal;
out rgm::vec3 vLightDirection;
out rgm::vec3 vLightPosition;
out rgm::vec2 vTexCoord;

void main()
{   
   rgm::vec4 pos  = uViewMatrix * uModelMatrix * aVertex;

    mat3 v3 = mat3(uViewMatrix);
    mat3 m3 = mat3(uModelMatrix);
    
    vPosition       = pos.xyz;
    vNormal         = v3 * m3 * aNormal;
    vLightDirection = v3 * uLightDirection;
    vLightPosition  = (uViewMatrix * rgm::vec4(uLightPosition, 1.0)).xyz;
    vTexCoord       = aTexCoord;

    gl_Position = uProjectionMatrix * pos;
}