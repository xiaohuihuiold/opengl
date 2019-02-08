#version 330 core

#define NR_POINT_LIGHTS 4
// 材质结构体
struct Material{
    // 漫反射颜色
    sampler2D diffuse;
    // 镜面反射颜色
    sampler2D specular;
    // 反光度
    float shininess;
};

// 定向光
struct DirLight{
    // 光照方向
    vec3 direction;
    // 冯氏光照模型
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    // 光源位置
    vec3 position;

    // 衰减常数项
    float constant;
    // 衰减一次项
    float linear;
    // 衰减二次项
    float quadrtic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight{
    vec3 position;
    vec3 direction;

    // 内切角
    float cutOff;
    // 内切角(第二个圆锥)
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 calcDirLight(DirLight light,vec3 normal,vec3 viewDir);
vec3 calcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir);
vec3 calcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir);

void main() {
    // 标准化法向量
    vec3 norm = normalize(Normal);
    // 视线方向，从片段到相机
    vec3 viewDir=normalize(viewPos-FragPos);

    vec3 result = calcDirLight(dirLight,norm,viewDir);
    for(int i=0;i<NR_POINT_LIGHTS;i++){
        result +=calcPointLight(pointLights[i],norm,FragPos,viewDir);
    }
    result +=calcSpotLight(spotLight,norm,FragPos,viewDir);

    FragColor = vec4( result ,1.0);
}

vec3 calcDirLight(DirLight light,vec3 normal,vec3 viewDir){
    // 变换光源照射方向为物体指向光源的方向
    vec3 lightDir = normalize(-light.direction);
    // 获取法线与光线的差，值越大光照越强
    float diff = max(dot(normal,lightDir),0.0);
    // 获取反射光照向量，需要的是光照方向
    vec3 reflectDir = reflect(-lightDir,normal);
    // 视线与光的反射值进行点乘求差值，并设置反光度
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    // 环境光照，材质使用漫反射材质
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
    // 漫反射，使用漫反射材质
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));
    // 镜面反射，使用镜面反射材质
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));

    // 构成冯氏光照模型
    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
    // 取得到光源的向量
    vec3 lightDir = normalize(light.position-fragPos);

    float diff = max(dot(normal,lightDir),0.0);
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    // 计算片段到光源的位置
    float distance = length(light.position-fragPos);
    // 1.0/(常数项+一次项*距离+二次项*距离*距离)
    float attenuation = 1.0/(light.constant+light.linear*distance+light.quadrtic*distance*distance);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));

    // 加上光的距离衰减
    return ambient + diffuse*attenuation + specular*attenuation;
}

vec3 calcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
    vec3 lightDir = normalize(light.position-fragPos);

    float diff = max(dot(normal,lightDir),0.0);
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    float distance = length(light.position-fragPos);
    float attenuation = 1.0/(light.constant+light.linear*distance+light.quadratic*distance*distance);

    // 计算片段与光照角度的余弦值
    float theta = dot(lightDir,normalize(-light.direction));
    // 内外余弦值差(cos(90)<cos(1))
    float epsilon = light.cutOff-light.outerCutOff;
    // 把聚光强度限制到0~1
    // 聚光强度 = (片段和光源的夹角-外圆锥余弦值)/内外圆锥余弦值差
    float intensity = clamp((theta-light.outerCutOff)/epsilon,0.0,1.1);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));

    diffuse *=intensity*attenuation;
    specular *=intensity*attenuation;

    return ambient + diffuse + specular;
}
