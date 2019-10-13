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
