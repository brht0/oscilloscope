#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;  

out vec2 outTex;

void main(){
	gl_Position = vec4((aPos * 2.0 - 1.0), 0.0, 1.0);
	outTex = aTex;
}
