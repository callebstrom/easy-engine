#version 450

layout (location = 0) in vec3 inPosition; 
layout (location = 1) in vec3 inColor;

smooth out vec3 color;

uniform mat4 mvp;

void main() { 
   gl_Position = /*mvp * */ vec4(inPosition, 1.0); 
   color = inColor; 
}