// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#version 430

uniform sampler2D uPosition;
uniform sampler2D uNormal;
uniform sampler2D uBaseColor;
uniform sampler2D uMRHA;
uniform sampler2D uDepth;

in vec3 vNormal;
in vec2 vTexCoord;

out vec4 oFragColor;

float scale(float value, float min, float max) {
  return (value - min) / (max - min);
}

vec3 scaleNormal(vec3 normal) {
  return (normal + 1.0) / 2.0;
}

void main()
{
    vec3 normal = texture(uNormal, vTexCoord).rgb;
    normal = scaleNormal(normal);
    oFragColor = vec4(normal, 1.0);
}
