#version 330 core

in vec2 outTex;
out vec4 color;

uniform sampler2D src1;

void main(){
    // color = vec4(outTex.y * outTex.x);
    color = texture(src1, outTex);
}
