#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int WINDOW_WIDTH = 1200;
int WINDOW_HEIGHT = 720;

void onFramebufferSizeCallback(GLFWwindow *, int, int);

void onKeyInput(GLFWwindow *);

int main() {
    //初始化glfw以及创建窗口
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Model", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "窗口创建失败" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 设置当前窗口为主线程上下文
    glfwMakeContextCurrent(window);

    // 添加窗口大小改变回调
    glfwSetFramebufferSizeCallback(window, onFramebufferSizeCallback);

    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "glad初始化失败!" << std::endl;
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        // 处理键盘事件
        onKeyInput(window);

        // 清除颜色缓冲
        glClearColor(0.5f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 交换颜色缓冲
        glfwSwapBuffers(window);
        // 检查触发事件
        glfwPollEvents();
    }

    // 清理资源
    glfwTerminate();

    return 0;
}

void onFramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
}

void onKeyInput(GLFWwindow *window) {
    // 检查ESC是否触发
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}