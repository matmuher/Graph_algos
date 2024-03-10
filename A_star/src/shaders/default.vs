#version 330 core

layout (location = 0) in vec3 dataPos;
layout (location = 1) in vec3 dataColor;

uniform vec3 shifts[2];

uniform int GridSize;
uniform float QuadWidth;

flat out int instanceID;
flat out vec3 color;

void main()
{
	vec3 scaledPos = dataPos * QuadWidth;

	int yShift = gl_InstanceID / GridSize;
	int xShift = int(mod(gl_InstanceID, GridSize));

	scaledPos.x -= 1;
	scaledPos.y += (1 - QuadWidth);

	scaledPos.x += xShift * QuadWidth;
	scaledPos.y -= yShift * QuadWidth;

	gl_Position = vec4(scaledPos, 1.);	
	instanceID = gl_InstanceID;
	color = dataColor;
}
