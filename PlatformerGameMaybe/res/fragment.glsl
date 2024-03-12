#version 330 core

in vec2 texCoords;

out vec4 outColor;

uniform sampler2D texSampler;

uniform int hasTex;
uniform vec3 objColor;

void main()
{
	if (hasTex == 0)
		outColor = vec4(objColor, 1.0);
	else if (hasTex == 1)
		outColor = texture(texSampler, texCoords);
}