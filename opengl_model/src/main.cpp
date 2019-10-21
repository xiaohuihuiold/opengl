#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "util/Util.h"
#include "shader/Shader.h"
#include "camera/Camera.h"
#include "model/Model.h"

#define WINDOW_TITLE "Model"

int WINDOW_WIDTH = 1200;
int WINDOW_HEIGHT = 720;

// 窗口大小改变的回调
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// 输入事件处理
void process_input(GLFWwindow *window);

// 鼠标事件处理
void process_mouse(GLFWwindow *window, double x, double y);

GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
};

// 相机
Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);

// 物体位置
glm::mat4 model = glm::mat4(1.0f);

// 渲染时间
double deltaTime = 0.0f;
double lastFrame = 0.0f;

// 鼠标位置
glm::vec2 mousePosition;

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // 注册窗口大小改变的函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, process_mouse);

    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        perror("glad初始化失败");
        glfwTerminate();
        return -1;
    }

    // 启用多重采样
    glEnable(GL_MULTISAMPLE);
    // 启用深度测试
    glEnable(GL_DEPTH_TEST);
    // 启用模板测试
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xff);
    // 模板和深度测试都只通过一个时保留模板值,都通过时将模板值替换为上面模板函数的ref: 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    // 线框模式
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 创建着色器
    Shader modelShader("../assets/shader/cube_vertex.glsl", "../assets/shader/cube_fragment.glsl");
    Shader lightShader("../assets/shader/light_vertex.glsl", "../assets/shader/light_fragment.glsl");
    Shader modelOutlineShader("../assets/shader/cube_vertex.glsl", "../assets/shader/outline_fragment.glsl");
    Shader depthShader("../assets/shader/depth_vertex.glsl", "../assets/shader/depth_fragment.glsl");

    Model ballModel("../assets/model/blender/ball.obj");
    Model headModel("../assets/model/blender/head.obj");

    // 加载并创建纹理
    //GLuint textureWall = loadImage("../assets/images/wall.jpg");
    //GLuint textureFace = loadImage("../assets/images/face.png");

    // 创建顶点缓存对象
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 创建光源顶点数组对象
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);
/*
    // 深度贴图帧缓冲对象
    GLuint depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    // 创建深度缓冲使用的2D纹理
    const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    GLuint depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                 nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 把纹理作为帧缓冲的深度缓冲
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

    modelShader.use();
    // 设置纹理位置
    //modelShader.setInt("box", 0);
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, textureWall);


    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, glm::vec3(3.0f, 1.0f, 1.0f));
    lightModel = glm::scale(lightModel, glm::vec3(0.1f, 0.1f, 0.1f));

    //model = glm::scale(model, glm::vec3(0.4, 0.4, 0.4));

    glm::vec3 objectColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    // 实现渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 在每次渲染开始时处理输入事件
        process_input(window);

      /*  glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
        glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f), glm::vec3(1.0));
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        depthShader.use();
        depthShader.setMat4("lightSpaceMatrix", lightProjection * lightView);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
*/
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        //model = glm::rotate(model, glm::radians((GLfloat) sin(glfwGetTime())), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::rotate(model, glm::radians((GLfloat) cos(glfwGetTime())), glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::rotate(model, glm::radians((GLfloat) cos(glfwGetTime() + 2.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
        // 清除缓冲区
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        // 对每个片段的模板值都设置为1
        glStencilFunc(GL_ALWAYS, 1, 0xff);
        // 启用模板缓冲写入
        glStencilMask(0xff);
        // 绘制箱子
        modelShader.use();
        modelShader.setMat4("model", model);
        modelShader.setMat4("view", camera.view);
        modelShader.setMat4("projection", camera.projection);
        modelShader.setVec3("objectColor", objectColor);
        modelShader.setVec3("lightColor", lightColor);
        modelShader.setVec3("lightPos", glm::vec3(3.0f, 1.0f, 1.0f));
        modelShader.setVec3("viewPos", camera.position);
        headModel.draw(modelShader);

        // 绘制轮廓
        // 只绘制上一步模板值没有被更新为1的片段
        glStencilFunc(GL_NOTEQUAL, 1, 0xff);
        // 禁用模板缓冲写入
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        modelOutlineShader.use();
        modelOutlineShader.setMat4("model", glm::scale(model, glm::vec3(1.02f, 1.02f, 1.02f)));
        modelOutlineShader.setMat4("view", camera.view);
        modelOutlineShader.setMat4("projection", camera.projection);
        headModel.draw(modelOutlineShader);
        glEnable(GL_DEPTH_TEST);

        glStencilFunc(GL_ALWAYS, 1, 0xff);
        glStencilMask(0xff);
        // 绘制光源
        lightShader.use();
        glBindVertexArray(lightVAO);
        lightShader.setMat4("model", lightModel);
        lightShader.setMat4("view", camera.view);
        lightShader.setMat4("projection", camera.projection);
        lightShader.setVec3("lightColor", lightColor);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 交换缓冲以及检查事件
        glfwSwapBuffers(window);
        glfwPollEvents();
        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
    }

    // 清理资源
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
    camera.updateSize(width, height);
}

// 输入事件处理
void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        // 按下esc后设置应当关闭窗口
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    // 根据时间差匀速
    camera.speed = 2.5f * deltaTime;
    // 前后移动
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.toFront();
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.toBack();
    }
    // 左右移动
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.toLeft();
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.toRight();
    }
}

// 鼠标事件处理
void process_mouse(GLFWwindow *window, double x, double y) {
    float deltaX = (float) x - mousePosition.x;
    float deltaY = mousePosition.y - (float) y;

    mousePosition.x = x;
    mousePosition.y = y;

    camera.updateMouse(deltaX, deltaY);

}