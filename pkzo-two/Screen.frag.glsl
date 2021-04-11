// Ice Engine
// Copyright 2020 Sean Farrell
// All rights reserved.

#version 430

uniform vec4      pkzo_BaseColorFactor;
uniform bool      pkzo_HasBaseColorMap;
uniform sampler2D pkzo_BaseColorMap;

in vec2 vTexCoord;

out vec4 pkzo_FragColor;

void main()
{
    if (pkzo_HasBaseColorMap)
    {
        pkzo_FragColor = texture(pkzo_BaseColorMap, vTexCoord) * pkzo_BaseColorFactor;
    }
    else
    {
        pkzo_FragColor = pkzo_BaseColorFactor;
    }
}
