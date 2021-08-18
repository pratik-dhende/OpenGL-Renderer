#version 330

in vec4 vs_positionColor;
in vec2 vs_positionTexCord;

uniform sampler2D texture0;

void main(){
    gl_FragColor = texture(texture0, vs_positionTexCord) * vs_positionColor;
}