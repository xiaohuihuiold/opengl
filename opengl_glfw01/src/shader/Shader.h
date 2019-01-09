//
// Created by xhh on 1/9/19.
//

#ifndef OPENGL_GLFW01_SHADER_H
#define OPENGL_GLFW01_SHADER_H


#include <glad/glad.h>

class Shader {
public:
    GLuint ID;
public:
    Shader(const char *vertexPath, const char *fragmentPath);

    void use();

    void setVec4(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

    void setVec3(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2);

    void setVec2(const std::string &name, GLfloat v0, GLfloat v1);

    void setBool(const std::string &name, bool value);

    void setInt(const std::string &name, GLint value);

    void setFloat(const std::string &name, GLfloat value);

private:
    void checkCompileError(GLuint shader);

    void checkLinkError(GLuint program);
};


#endif //OPENGL_GLFW01_SHADER_H
