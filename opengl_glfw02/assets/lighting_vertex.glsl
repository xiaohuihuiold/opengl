#version 330 core
layout (location = 0) in vec3 aPos;
// 顶点法向量
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
// 片段位置
out vec3 FragPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main() {
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(aPos.x ,aPos.y ,aPos.z ,1.0);
    // 片段在世界坐标中的位置
    // 所以只需要乘上模型矩阵
    FragPos = vec3(modelMatrix * vec4(aPos ,1.0));
    Normal = aNormal;
}
