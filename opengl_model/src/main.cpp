#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader/Shader.h"
#include "stb_image/stb_image.h"

#define WINDOW_TITLE "Model"

int WINDOW_WIDTH = 1200;
int WINDOW_HEIGHT = 720;

GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
};

GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
};

// 窗口大小改变的回调
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// 输入事件处理
void process_input(GLFWwindow *window);

// 图片加载
GLuint loadImage(const char *path);

int main(int argc, char **argv) {
    // 初始化glfw
    glfwInit();

    // 设置版本为3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 设置opengl为核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 设置采样
    glfwWindowHint(GLFW_SAMPLES, 4);

    // 如果是macos
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif

    // 创建窗口并设置上下文
    // monitor: 为空则是窗口模式
    // share: 共享资源的窗口,为空则不共享
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        perror("窗口创建失败");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // 注册窗口大小改变的函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        perror("glad初始化失败");
        glfwTerminate();
        return -1;
    }

    // 启用多重采样
    glEnable(GL_MULTISAMPLE);
    // 线框模式
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 创建着色器
    Shader shader("../assets/shader/test_vertex.glsl", "../assets/shader/test_fragment.glsl");

    // 加载并创建纹理
    GLuint textureWall = loadImage("../assets/images/wall.jpg");
    GLuint textureFace = loadImage("../assets/images/face.png");

    // 创建顶点缓存对象
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 创建顶点数组对象
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // 链接顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);
    // 链接纹理坐标
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(1);

    // 创建索引缓冲对象
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    shader.use();

    glUniform1i(glGetUniformLocation(shader.id, "wallTexture"), 0);
    glUniform1i(glGetUniformLocation(shader.id, "faceTexture"), 1);

    // 实现渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 在每次渲染开始时处理输入事件
        process_input(window);

        // 清除缓冲区
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureWall);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureFace);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 交换缓冲以及检查事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

// 窗口大小改变的回调
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // 窗口大小改变时重新设置视口大小
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    // 设置视口,渲染窗口的尺寸大小
    // 左下角起点
    glViewport(0, 0, width, height);
}

// 输入事件处理
void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        // 按下esc后设置应当关闭窗口
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

GLuint loadImage(const char *path) {
    // 创建并绑定texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // 加载图片并获取宽高通道信息
    int width;
    int height;
    int nrChannel;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannel, 0);
    if (!data) {
        perror("材质加载失败");
    }

    // 根据数据生成纹理
    GLenum format = GL_RGB;
    if (nrChannel == 4) {
        format = GL_RGBA;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    // 生成多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);

    // 纹理环绕方式 重复
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 纹理过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 释放
    stbi_image_free(data);
    return texture;
}