//
// Created by WIN10 on 2019/10/12.
//

#ifndef OPENGL_MODEL_SHADER_H
#define OPENGL_MODEL_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    GLuint id;
public:
    Shader(const char *vertexPath, const char *fragmentPath);

    /**
     * 使用当前着色器
     */
    void use();

    /**
     * 设置bool值
     * @param name uniform名
     * @param value bool值
     */
    void setBool(const char *name, GLboolean value);

    /**
     * 设置int值
     * @param name  uniform名
     * @param value int值
     */
    void setInt(const char *name, GLint value);

    /**
     * 设置float值
     * @param name  uniform名
     * @param value float值
     */
    void setFloat(const char *name, GLfloat value);

    /// 设置向量

    void setVec2(const char *name, GLfloat v0, GLfloat v1);

    void setVec2(const char *name, const glm::vec2 &vec2);

    void setVec3(const char *name, GLfloat v0, GLfloat v1, GLfloat v2);

    void setVec3(const char *name, const glm::vec3 &vec3);

    void setVec4(const char *name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

    void setVec4(const char *name, const glm::vec4 &vec4);

    /// 设置矩阵

    void setMat2(const char *name, const glm::mat2 &mat2);

    void setMat3(const char *name, const glm::mat3 &mat3);

    void setMat4(const char *name, const glm::mat4 &mat4);

private:
    /**
     * 加载glsl文件
     * @param glslPath glsl文件路径
     * @return
     */
    const char *loadGLSL(const char *glslPath);

    /**
     * 检查着色器编译错误
     * @param shader 着色器
     * @return
     */
    bool checkCompileError(GLuint shader);

    /**
     * 检查着色器程序连接错误
     * @param program 着色器程序
     * @return
     */
    bool checkLinkError(GLuint program);
};

#endif //OPENGL_MODEL_SHADER_H
