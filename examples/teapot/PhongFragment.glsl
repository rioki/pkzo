#version 400

uniform sampler2D uTexture;

in vec2 vTexCoord;
in vec4 vColor;

out vec4 gl_FragColor;

void main()
{	    
	gl_FragColor = texture(uTexture, vTexCoord) * vColor;	
}
