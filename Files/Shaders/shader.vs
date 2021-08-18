#version 330

attribute vec3 position;

void main(){
	gl_position = vec4(position, 1);
}