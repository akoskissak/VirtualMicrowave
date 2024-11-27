#version 330 core

out vec4 FragColor;

in vec3 color;

in vec2 texCoord;

uniform sampler2D tex4;

void main()
{
	vec4 texColor = texture(tex4, texCoord);
	if(texColor.a < 0.1)
		discard;
	FragColor = texColor;

}