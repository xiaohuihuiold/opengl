//
// Created by WIN10 on 2019/10/12.
//

#ifndef OPENGL_MODEL_SHADER_H
#define OPENGL_MODEL_SHADER_H


#include <glad/glad.h>

class Shader {
public:
    GLuint id;
public:
    Shader(const char *vertexPath, const char *fragmentPath);

    // 使用当前着色器
    void use();

private:
    // 加载glsl文件
    const char *loadGLSL(const char *glslPath);

    // 检查着色器编译错误
    bool checkCompileError(GLuint shader);

    // 检查着色器程序连接错误
    bool checkLinkError(GLuint program);
};

#endif //OPENGL_MODEL_SHADER_H
