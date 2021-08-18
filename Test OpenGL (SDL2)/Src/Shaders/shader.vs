#version 330

layout (location = 0) in vec3 mesh_position;
layout (location = 1) in vec4 mesh_positionColor;
layout (location = 2) in vec2 mesh_positionTexCord;

out vec4 vs_positionColor;
out vec2 vs_positionTexCord;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionPerspectiveMatrix;

void main(){
	mat4 renderMatrix = projectionPerspectiveMatrix * viewMatrix * modelMatrix;
	gl_Position = vec4(mesh_position, 1);

	vs_positionColor = mesh_positionColor;
	vs_positionTexCord = mesh_positionTexCord;
}