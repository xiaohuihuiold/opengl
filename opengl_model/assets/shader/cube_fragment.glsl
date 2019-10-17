#version 330 core

uniform sampler2D texture_diffuse1;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

void main(){
    // 环境光
    float ambientStrength = 0.1;
    vec3 ambient= ambientStrength * lightColor;
    // 计算从片段到光源的向量
    vec3 lightDir = normalize(lightPos - FragPos);

    // 漫反射光照
    // 点乘获取余弦值
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 镜面光照
    // 计算片段到视角位置的向量
    vec3 viewDir = normalize(viewPos - FragPos);
    // 光源向量取反
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * lightColor;

    vec3 result = (ambient + diffuse + specular)* objectColor;

    FragColor = vec4(vec3(texture(texture_diffuse1, TexCoords)) *result, 1.0);
}
