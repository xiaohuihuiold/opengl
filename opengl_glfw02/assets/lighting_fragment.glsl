#version 330 core
// 顶点法向量
in vec3 Normal;
// 片段位置
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
// 观察位置
uniform vec3 viewPos;

void main() {
    // 标准化法向量
    vec3 norm = normalize(Normal);

    // 环境光照强度
    float ambientStrength = 0.1;
    // 计算环境光照分量
    vec3 ambient = ambientStrength * lightColor;

    // 获得光源和片段位置之间向量差，并标准化
    vec3 lightDir = normalize(lightPos - FragPos);
    // 求光源的影响，并不为负数
    float diff = max(dot(norm ,lightDir) ,0.0);
    // 计算漫反射分量
    vec3 diffuse = diff * lightColor;

    // 镜面反射强度
    float specularStrangrh = 0.5;
    // 视线位置和片段位置向量差，得到视线方向向量
    vec3 viewDir = normalize(viewPos - FragPos);
    // 获取光照反射向量
    // lightDir取反是因为求反射向量需要的是光源指向片段位置的向量
    vec3 reflectDir = reflect(-lightDir , norm);
    // max同漫反射,32是反光度
    float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
    // 根据反射强度，反光度，光照颜色计算镜面分量
    vec3 specular = specularStrangrh * spec * lightColor;

    // (环境光照(全局) + 模型漫反射) * 模型颜色
    // 得到最终的颜色
    vec3 result = (diffuse + ambient + specular) * objectColor;
    FragColor = vec4( result ,1.0);
}
