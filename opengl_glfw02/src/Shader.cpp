//
// Created by xhh on 2/3/19.
//

#include "Shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexStr;
    std::string fragmentStr;

    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);

        std::stringstream vertexStream;
        std::stringstream fragmentStream;

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        vertexStr = vertexStream.str();
        fragmentStr = fragmentStream.str();
    } catch (std::ifstream::failure &e) {
        perror(e.what());
    }

    const char *vertexSource = vertexStr.c_str();
    const char *fragmentSource = fragmentStr.c_str();

    GLuint vertexShader;
    // 创建着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 设置源
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    // 编译着色器
    glCompileShader(vertexShader);
    // 检查编译错误
    checkCompileError(vertexShader);

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    checkCompileError(fragmentShader);

    // 创建着色器程序
    ID = glCreateProgram();
    // 添加顶点着色器
    glAttachShader(ID, vertexShader);
    // 添加片元着色器
    glAttachShader(ID, fragmentShader);
    // 链接程序
    glLinkProgram(ID);
    // 检查链接错误
    checkLinkError(ID);

    // 链接成功后删除着色器释放资源
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::checkCompileError(GLuint shader) {
    int success;
    char infoLog[1024];
    // 获取编译状态
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // 获取信息
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cout << "shader compile failed:" << infoLog << std::endl;
    }
}

void Shader::checkLinkError(GLuint program) {
    int success;
    char infoLog[1024];
    // 获取链接状态
    glGetShaderiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        // 获取信息
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        std::cout << "shader program link failed:" << infoLog << std::endl;
    }
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat4) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
}

void Shader::setVec4(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2, v3);
}

void Shader::setVec3(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec3) {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec3[0]);
}

void Shader::setVec2(const std::string &name, GLfloat v0, GLfloat v1) {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), v0, v1);
}

void Shader::setBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, GLint value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, GLfloat value) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}


