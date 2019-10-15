//
// Created by WIN10 on 2019/10/12.
//

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include "Shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    // 编译顶点着色器
    const char *vertexSource = loadGLSL(vertexPath);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    delete vertexSource;
    glCompileShader(vertexShader);
    if (!checkCompileError(vertexShader)) {
        return;
    }

    // 编译片元着色器
    const char *fragmentSource = loadGLSL(fragmentPath);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    delete fragmentSource;
    glCompileShader(fragmentShader);
    if (!checkCompileError(fragmentShader)) {
        return;
    }

    // 创建着色器程序
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    if (!checkLinkError(program)) {
        return;
    }
    this->id = program;

    // 删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(this->id);
}

const char *Shader::loadGLSL(const char *glslPath) {
    std::string glslStr;
    std::ifstream glslFile;
    glslFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        glslFile.open(glslPath);
        std::stringstream glslStream;
        glslStream << glslFile.rdbuf();
        glslStr = glslStream.str();
        glslFile.close();
    } catch (std::ifstream::failure &e) {
        perror(e.what());
    }
    char *str = new char[glslStr.length() + 1];
    strcpy(str, glslStr.c_str());
    return str;
}

bool Shader::checkCompileError(GLuint shader) {
    int success;
    char info[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, info);
        std::cout << "着色器编译错误:" << info << std::endl;
        return false;
    }
    return true;
}

bool Shader::checkLinkError(GLuint program) {
    int success;
    char info[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, nullptr, info);
        std::cout << "连接着色器出错:" << info << std::endl;
        return false;
    }
    return true;
}

void Shader::setBool(const char *name, GLboolean value) {
    glUniform1i(glGetUniformLocation(this->id, name), (GLint) value);
}

void Shader::setInt(const char *name, GLint value) {
    glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::setFloat(const char *name, GLfloat value) {
    glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::setVec2(const char *name, GLfloat v0, GLfloat v1) {
    glUniform2f(glGetUniformLocation(this->id, name), v0, v1);
}

void Shader::setVec2(const char *name, const glm::vec2 &vec2) {
    glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(vec2));
}

void Shader::setVec3(const char *name, GLfloat v0, GLfloat v1, GLfloat v2) {
    glUniform3f(glGetUniformLocation(this->id, name), v0, v1, v2);
}

void Shader::setVec3(const char *name, const glm::vec3 &vec3) {
    glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(vec3));
}

void Shader::setVec4(const char *name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glUniform4f(glGetUniformLocation(this->id, name), v0, v1, v2, v3);
}

void Shader::setVec4(const char *name, const glm::vec4 &vec4) {
    glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(vec4));
}

void Shader::setMat2(const char *name, const glm::mat2 &mat2) {
    glUniformMatrix2fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(mat2));
}

void Shader::setMat3(const char *name, const glm::mat3 &mat3) {
    glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(mat3));
}

void Shader::setMat4(const char *name, const glm::mat4 &mat4) {
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(mat4));
}
