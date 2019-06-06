#version 450

layout (location = 0) in vec3 vertexPosition_modelspace; 
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 vertexNormal_modelspace;


smooth out vec3 frag_color;
out vec3 frag_vertexPosition_modelspace;
out vec3 frag_vertexNormal_modelspace;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 view;
uniform vec3 lightPosition_worldspace;

void main() { 
	gl_Position = mvp * vec4(vertexPosition_modelspace, 1.0); 
	frag_color = vertexColor;
	frag_vertexPosition_modelspace = vertexPosition_modelspace;
	frag_vertexNormal_modelspace = vertexNormal_modelspace;
    
}