#version 330 core

out vec4 FragColor;
flat in int instanceID;
flat in vec3 color;

void main()
{
	FragColor = vec4(color, 1.);	
}
