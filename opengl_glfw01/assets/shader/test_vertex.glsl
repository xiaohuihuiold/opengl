#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

// 模型矩阵
uniform mat4 modelMatrix;
// 观察矩阵
uniform mat4 viewMatrix;
// 投影矩阵
uniform mat4 projectionMatrix;

void main() {
    // 需要从右向左读
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos.x,aPos.y,aPos.z,1.0);
    TexCoord=aTexCoord;
}