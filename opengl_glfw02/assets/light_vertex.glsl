#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main() {
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(aPos.x ,aPos.y ,aPos.z ,1.0f);
}
