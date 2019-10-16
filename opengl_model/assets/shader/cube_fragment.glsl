#version 330 core

uniform sampler2D box;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

void main(){
    // 环境光
    float ambientStrength = 0.1;
    vec3 ambient= ambientStrength * lightColor;

    // 漫反射光照
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse)* objectColor;

    FragColor = vec4(vec3(texture(box, TexCoords)) *result, 1.0);
}
