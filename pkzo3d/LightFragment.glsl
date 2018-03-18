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

#define AMBIENT_LIGHT 0
#define DIFFUSE_LIGHT 1
#define POINT_LIGHT   2
#define SPOT_LIGHT    3

uniform rgm::vec3      uMaterialAlbedo;
uniform float     uMaterialRoughness;
uniform bool      uMaterialHasTexture;
uniform sampler2D uMaterialTexture;

uniform int       uLightType;
uniform float     uLightRange;
uniform float     uLightCutoff;
uniform rgm::vec3      uLightColor;

// TMP
uniform rgm::vec3 uLightDirection;
uniform rgm::vec3 uLightPosition;

in rgm::vec3 vPosition;
in rgm::vec3 vNormal;
in rgm::vec3 vLightDirection;
in rgm::vec3 vLightPosition;
in rgm::vec2 vTexCoord;

out rgm::vec4 oFragColor;

float lambert( rgm::vec3 l, rgm::vec3 n) {
    return max(0.0, dot(l, n));
}

void main()
{
    rgm::vec3 N = normalize(vNormal);
    rgm::vec3 L;

    switch (uLightType)
    {
        case DIFFUSE_LIGHT:
            L = normalize(vLightDirection);
            break;
        case POINT_LIGHT:
            L = normalize(vLightPosition - vPosition);
            break;
        case SPOT_LIGHT:
            L = normalize(vLightPosition - vPosition);
            break;
    }

    float diffuse = lambert(L, N);
   rgm::vec4 dc = rgm::vec4(uMaterialAlbedo * uLightColor * diffuse, 1.0);

    gl_FragColor = dc; 
}
