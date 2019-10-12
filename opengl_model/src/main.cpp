#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_TITLE "Model"

int WINDOW_WIDTH = 1200;
int WINDOW_HEIGHT = 720;

// 窗口大小改变的回调
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// 输入事件处理
void process_input(GLFWwindow *window);

int main(int argc, char **argv) {
    // 初始化glfw
    glfwInit();

    // 设置版本为3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 设置opengl为核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        perror("glad初始化失败");
        glfwTerminate();
        return -1;
    }

    // 注册窗口大小改变的函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 实现渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 在每次渲染开始时处理输入事件
        process_input(window);

        // 清除缓冲区
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 交换缓冲以及检查事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理资源
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
        glfwSetWindowShouldClose(window, TRUE);
    }
}