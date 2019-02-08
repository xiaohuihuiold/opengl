#version 330 core
// 材质结构体
struct Material{
    // 漫反射颜色
    sampler2D diffuse;
    // 镜面反射颜色
    sampler2D specular;
    // 反光度
    float shininess;
};

// 光照结构体
struct Light{
    // 光源位置
    vec3 position;
    // 光照方向
    vec3 direction;
    // 内光切
    float cutOff;
    // 外圆锥光切
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

// 顶点法向量
in vec3 Normal;
// 片段位置
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

// 观察位置
uniform vec3 viewPos;
// 材质
uniform Material material;
// 光源
uniform Light light;

void main() {
    // 标准化法向量
    vec3 norm = normalize(Normal);

    // 获得光源和片段位置之间向量差，并标准化
    vec3 lightDir = normalize(light.position - FragPos);

    // 获取光照方向和片段方向的余弦值
    // 取反是需要指向光源
    float theta = dot(lightDir,normalize(-light.direction));
    // 内外圆锥余弦值差
    float epsilon = light.cutOff - light.outerCutOff;
    // 聚光强度 = (片段和光源的夹角-外圆锥余弦值)/内外圆锥余弦值差
    float intensity = clamp((theta - light.outerCutOff)/epsilon ,0.0 ,1.0);

    // 光源距离片段的距离
    float distance = length(light.position - FragPos);
    // 计算光的衰减
    // 1.0/(常数项+一次项*距离+二次项*距离*距离)
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    // 计算环境光照分量
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
    // 求光源的影响，并不为负数
    float diff = max(dot(norm ,lightDir) ,0.0);
    // 计算漫反射分量
    vec3 diffuse =light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));

    // 视线位置和片段位置向量差，得到视线方向向量
    vec3 viewDir = normalize(viewPos - FragPos);
    // 获取光照反射向量
    // lightDir取反是因为求反射向量需要的是光源指向片段位置的向量
    vec3 reflectDir = reflect(-lightDir , norm);
    // max同漫反射,32是反光度
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    // 根据反射强度，反光度，光照颜色计算镜面分量
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));

    // 计算光照衰减
    diffuse *=attenuation;
    specular *=attenuation;

    // 平滑光
    diffuse *=intensity;
    specular *=intensity;

    // (环境光照(全局) + 模型漫反射) * 模型颜色
    // 得到最终的颜色
    vec3 result = diffuse + ambient + specular;
    FragColor = vec4( result ,1.0);
}
