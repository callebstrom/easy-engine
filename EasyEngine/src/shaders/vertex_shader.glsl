#version 330 core

in vec2 position;
out vec4 Color;

void main()
{
	Color = vec4(0.5, 0.5, 0.5, 1.0);
    gl_Position = vec4(position, 0.0, 1.0);
}