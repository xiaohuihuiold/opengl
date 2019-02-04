# opengl_glfw02
  OpenGL 光照学习
  
## 笔记
  * 冯氏光照模型
    * 环境光照(ambient)
    * 漫反射(diffuse)
    * 镜面反射(specular)
  * 环境光照
    * 光源乘上环境因子
      ```c
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;
      ```
  * 漫反射
    * 给顶点添加法向量
    * 获得片段在世界中的位置
    * 根据片段和光源位置计算向量差
      ```c
      vec3 lightDir = normalize(lightPos - FragPos);
      ```
    * 法向量和上一步的结果进行点乘求对光源的影响
      ```c
        float diff = max(dot(norm ,lightDir) ,0.0);
      ```
    * 乘上光源
      ```c
        vec3 diffuse = diff * lightColor;
      ```
  * 最终颜色
    * 环境光照加上漫反射的值乘上物体颜色
      ```c
        vec3 result = (diffuse + ambient) * objectColor;
      ```