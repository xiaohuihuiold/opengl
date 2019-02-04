//
// Created by xhh on 2/3/19.
//

#ifndef OPENGL_GLFW02_SHADER_H
#define OPENGL_GLFW02_SHADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    GLuint ID;
public:
    Shader(const char *vertexPath, const char *fragmentPath);

    void use();

    void setMat4(const std::string &name, const glm::mat4 &mat4);

    void setVec4(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

    void setVec3(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2);

    void setVec3(const std::string &name, const glm::vec3 &vec3);

    void setVec2(const std::string &name, GLfloat v0, GLfloat v1);

    void setBool(const std::string &name, bool value);

    void setInt(const std::string &name, GLint value);

    void setFloat(const std::string &name, GLfloat value);

private:
    void checkCompileError(GLuint shader);

    void checkLinkError(GLuint program);
};


#endif //OPENGL_GLFW02_SHADER_H
