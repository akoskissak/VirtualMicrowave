#version 330 core

out vec4 FragColor;

in vec3 color;

in vec2 texCoord;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;

void main()
{
	vec4 texColor = texture(tex0, texCoord);
	if(texColor.a < 0.1)
		discard;
	FragColor = texColor;

}