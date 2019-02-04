#version 330 core
// 顶点法向量
in vec3 Normal;
// 片段位置
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;

void main() {
    // 环境光照强度
    float ambientStrength = 0.1;
    // 计算环境光照分量
    vec3 ambient = ambientStrength * lightColor;

    // 标准化法向量
    vec3 norm = normalize(Normal);
    // 获得光源和片段位置之间向量差，并标准化
    vec3 lightDir = normalize(lightPos - FragPos);
    // 求光源的影响，并不为负数
    float diff = max(dot(norm ,lightDir) ,0.0);
    // 计算漫反射分量
    vec3 diffuse = diff * lightColor;

    // (环境光照(全局) + 模型漫反射) * 模型颜色
    // 得到最终的颜色
    vec3 result = (diffuse + ambient) * objectColor;
    FragColor = vec4( result ,1.0);
}
