#version 400 core

uniform mat4 uModelMatrix;

layout (location = 0) in vec4 iPosition;

void main() {
    gl_Position = uModelMatrix * iPosition;
}

