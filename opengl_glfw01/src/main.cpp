#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader/Shader.h"
#include "stb_image.h"

#define WINDOW_TITLE "OpenGL"

int WINDOW_WIDTH = 1200;
int WINDOW_HEIGHT = 800;

GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

glm::vec3 cubePosition[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 3.0f, -1.0f),
        glm::vec3(0.0f, -2.0f, 1.0f),
        glm::vec3(3.0f, 2.0f, -2.0f),
        glm::vec3(0.0f, -3.0f, 2.0f),
        glm::vec3(3.0f, 3.0f, 3.0f),
};

GLfloat texCoords[] = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.5f, 1.0f
};

GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
};

/*// 相机位置向量
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
// 相机观察目标向量
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
// 相机位置减去目标向量取得相机方向,此处反向减求得正方向
glm::vec3 cameraDirection = glm::normalize(cameraTarget - cameraPos);
// 上向量
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
// 上向量与相机位置叉乘取得与他们垂直的右轴
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
// 相机右轴与相机方向叉乘取得上轴
glm::vec3 cameraUp = glm::cross(cameraRight, cameraDirection);*/

// 相机位置
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
// 相机指向
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
// 相机上轴？
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// 增量时间
float deltaTime = 0.0f;
// 最后一帧的时间
float lastFrame = 0.0f;

// 俯仰角
float pitch = 0.0f;
// 偏航角
float yaw = 0.0f;
// 鼠标是否是第一次移动
bool isFirstMouse = true;
// 记录鼠标偏移xy值
double lastX = WINDOW_WIDTH / 2.0;
double lastY = WINDOW_HEIGHT / 2.0;

void processInput(GLFWwindow *);

void mouseCallback(GLFWwindow *, double xpos, double ypos);

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create openGL window
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        perror("Create openGL window failed");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // 设置捕获光标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // 设置鼠标回调
    glfwSetCursorPosCallback(window, mouseCallback);
    // 窗口大小改变回调
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        perror("Init GLAD failed");
        glfwTerminate();
        return -1;
    }

    // 启用深度缓冲(Z缓冲)
    glEnable(GL_DEPTH_TEST);
    // 启用多重采样
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 顶点数组对象
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // 顶点缓冲对象
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* GLuint EBO;
     glGenBuffers(1, &EBO);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
 */
    Shader shader("../assets/shader/test_vertex.glsl", "../assets/shader/test_fragment.glsl");

    // 模型顶点传递给顶点着色器
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    // 模型材质顶点传递给着色器
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 重复
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 取临近色值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width;
    int height;
    int nrChannels;
    unsigned char *data = stbi_load("../assets/flutter.png", &width, &height, &nrChannels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    // 透视投影矩阵
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f,
                                            100.0f);
    while (!glfwWindowShouldClose(window)) {
        float currentTime = (float) glfwGetTime();
        // 获取上一帧绘制时间
        deltaTime = currentTime - lastFrame;
        // 设置最后一帧开始绘制的时间
        lastFrame = currentTime;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清除颜色缓冲以及深度缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

        shader.use();

        // 根据宽高比创建投影矩阵
        projection = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f,
                                      100.0f);

        glm::mat4 view = glm::mat4(1.0f);
        // lookAt矩阵 相机位置，观察目标，上向量
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        GLint viewLocation = glGetUniformLocation(shader.ID, "viewMatrix");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

        GLint projectionLocation = glGetUniformLocation(shader.ID, "projectionMatrix");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        for (int i = 0; i < 6; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePosition[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            GLint modelLocation = glGetUniformLocation(shader.ID, "modelMatrix");
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    // 相机移动速度
    // 乘上增量时间使得移动更加平滑
    float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        // 相机前进
        // 相机位置直接加上前进向量
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        // 相机后退
        // 和上面相反，所以直接减就行了
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        // 相机向左移动
        // 先通过叉乘创建右向量
        // 再减去右向量达到向左移动的目的
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        // 相机向右移动
        // 同上
        // 只不过向右移动直接加上就行了
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        // 相机向上移动
        // 直接加上上向量就行了
        cameraPos += cameraSpeed * cameraUp;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        // 相机向下移动
        // 和上面相反,直接减去
        cameraPos -= cameraSpeed * cameraUp;
    }
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    // 灵敏度
    float sensitivity = 0.1f;
    if (isFirstMouse) {
        // 如果是第一次调用，就先赋值
        lastX = xpos;
        lastY = ypos;
        isFirstMouse = false;
    }
    // 鼠标xy偏移值，乘上灵敏度
    double xoffset = (xpos - lastX) * sensitivity;
    double yoffset = (lastY - ypos) * sensitivity;

    // 记录本次鼠标的偏移值
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    // 根据鼠标xy运动方向进行变换角度
    yaw += xoffset;
    pitch += yoffset;

    // 限制俯仰角的角度
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    // 设置新的相机朝向
    glm::vec3 front;

    //    俯仰角计算                  偏航角计算
    //        y                         z
    //        |     /                   |     /
    //        |    /|                   |    /|
    //        |   / |                   |   / |
    //        |  /  | sin(pitch)        |  /  | sin(yaw)
    //        | /   |                   | /   |
    //        |/)pit|                   |/)yaw|
    // ----------------- x/z     ----------------- x
    //        |   cos(pitch)            |   cos(yaw)
    //        |                         |
    //        |                         |
    //        |                         |
    front.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));

    // 转换为单位向量
    cameraFront = glm::normalize(front);
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    glViewport(0, 0, width, height);
}