#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "Shader.h"

#define WINDOW_TITLE "OpenGL Light"

int WINDOW_WIDTH = 1200;
int WINDOW_HEIGHT = 720;

GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

// 相机位置
glm::vec3 cameraPos;
// 相机朝向
glm::vec3 cameraFront;

// 相机俯仰角
float pitch = 0.0f;
// 相机偏航角
float yaw = -90.0f;

// 增量时间
float deltaTime = 1.0f;
float lastTime = 0.0f;

// 记录鼠标位置
bool isFirstMouse = true;
float lastX = (float) WINDOW_WIDTH / 2.0f;
float lastY = (float) WINDOW_HEIGHT / 2.0f;

GLuint loadTexture(const char *);

void onKeyInput(GLFWwindow *);

void onMouseCallback(GLFWwindow *, double, double);

void onFramebufferSizeCallback(GLFWwindow *, int, int);

int main() {
    glfwInit();
    // OpenGL 3.3(MAJOR.MINOR)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 使用核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 设置采样
    glfwWindowHint(GLFW_SAMPLES, 4);
    // 窗口尺寸不可变
    //glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);

    // 创建宽高1200/720名为 OpenGL Light的窗口
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "窗口创建失败!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // 设置捕获鼠标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // 鼠标位置回调
    glfwSetCursorPosCallback(window, onMouseCallback);
    // 帧缓冲大小改变回调
    glfwSetFramebufferSizeCallback(window, onFramebufferSizeCallback);

    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "glad初始化失败!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 启用深度缓冲
    glEnable(GL_DEPTH_TEST);
    // 启用多重采样
    glEnable(GL_MULTISAMPLE);

    // 光源着色器
    Shader lampShader("../assets/lamp_vertex.glsl", "../assets/lamp_fragment.glsl");
    // 光照着色器
    Shader lightingShader("../assets/lighting_vertex.glsl", "../assets/lighting_fragment.glsl");

    // 生成顶点数组对象,顶点缓冲对象
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 复制到缓冲的内存中
    // GL_ARRAY_BUFFER：目标缓冲类型
    // sizeof(vertices)：传输的数据大小
    // vertices：发送的数据
    // GL_STATIC_DRAW：数据几乎不会改变
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 生成立方体顶点数组对象
    GLuint cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    // 绑定顶点缓冲对象，以便取值
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 0: 在顶点着色器中的location
    // 3: 顶点属性大小
    // GL_FLOAT：指定数据类型
    // GL_FALSE：是否标准化
    // 3*sizeof(float)：下一个元素需要跳过的步长
    // (void*)0：数据偏移(字节)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    // 启用下标0的顶点数组参数
    glEnableVertexAttribArray(0);
    // 传递立方体顶点法向量
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // 传递材质坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // 生成光照顶点数组对象
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 传递立方体顶点坐标
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    GLuint diffuseMap = loadTexture("../assets/container2.png");
    GLuint specularMap = loadTexture("../assets/container2_specular.png");

    // 初始化相机位置以及朝向
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    // 视图矩阵
    // cameraPos：相机位置
    // cameraPos+cameraFront：观察目标
    // vec3：世界上向量
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
    // 透视投影
    // 45.0f：fov 视野，转换为弧度制
    // 宽高比，使得物体不会变形
    // 0.1f：平截头近平面
    // 100.0f：平截头远平面
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

    glm::vec3 pointLightPositions[] = {
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(7.0f, 0.0f, 1.0f),
            glm::vec3(9.0f, 6.0f, 6.0f),
            glm::vec3(9.0f, 1.0f, 1.0f),
    };

    // 检查是否被要求退出
    while (!glfwWindowShouldClose(window)) {
        // 计算上一祯绘制时间
        deltaTime = (float) glfwGetTime() - lastTime;
        lastTime = (float) glfwGetTime();

        // 每帧开始处理键盘输入
        onKeyInput(window);

        // 更新视图和投影
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
        proj = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

        glClearColor(0.5f, 0.5f, 0.6f, 1.0f);
        // 清除颜色缓冲，清除深度缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /*   float radius = 1.5f;
           float camX = sin(glfwGetTime()) * radius;
           float camZ = cos(glfwGetTime()) * radius;
           lightPos = glm::vec3(camX, camX, camZ);*/

        lightingShader.use();
        lightingShader.setVec3("viewPos", cameraPos);
        lightingShader.setMat4("viewMatrix", view);
        lightingShader.setMat4("projMatrix", proj);
        // 设置光照属性
        lightingShader.setInt("material.diffuse", 0);
        lightingShader.setInt("material.specular", 1);
        lightingShader.setFloat("material.shininess", 32.0f);
        // 设置定向光源
        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // 设置点光源
        // point light 1
        lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("pointLights[0].constant", 1.0f);
        lightingShader.setFloat("pointLights[0].linear", 0.09);
        lightingShader.setFloat("pointLights[0].quadratic", 0.032);
        // point light 2
        lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("pointLights[1].constant", 1.0f);
        lightingShader.setFloat("pointLights[1].linear", 0.09);
        lightingShader.setFloat("pointLights[1].quadratic", 0.032);
        // point light 3
        lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("pointLights[2].specular", 0.0f, 1.0f, 1.0f);
        lightingShader.setFloat("pointLights[2].constant", 1.0f);
        lightingShader.setFloat("pointLights[2].linear", 0.09);
        lightingShader.setFloat("pointLights[2].quadratic", 0.032);
        // point light 4
        lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("pointLights[3].constant", 1.0f);
        lightingShader.setFloat("pointLights[3].linear", 0.09);
        lightingShader.setFloat("pointLights[3].quadratic", 0.032);
        // 设置聚光源/手电筒
        lightingShader.setVec3("spotLight.position", cameraPos);
        lightingShader.setVec3("spotLight.direction", cameraFront);
        lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotLight.constant", 1.0f);
        lightingShader.setFloat("spotLight.linear", 0.09);
        lightingShader.setFloat("spotLight.quadratic", 0.032);
        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        // 绑定顶点数组
        glBindVertexArray(cubeVAO);
        // 激活绑定纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        for (int i = 0; i < 10; i += 2) {
            for (int j = 0; j < 10; j += 2) {
                for (int k = 0; k < 10; k += 2) {
                    glm::mat4 cubeModel = glm::mat4(1.0f);
                    cubeModel = glm::translate(cubeModel, glm::vec3(i, j, k));
                    lightingShader.setMat4("modelMatrix", cubeModel);
                    // 绘制三角形数组
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        }

        // 使用着色器程序
        lampShader.use();
        // 绑定顶点数组
        glBindVertexArray(lightVAO);
        glm::mat4 model = glm::mat4(1.0f);
        for (int i = 0; i < 4; i += 1) {
            // 把模型，观察，投影矩阵传递到着色器
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lampShader.setMat4("modelMatrix", model);
            lampShader.setMat4("viewMatrix", view);
            lampShader.setMat4("projMatrix", proj);
            // 绘制三角形数组
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // 交换颜色缓冲，绘制
        glfwSwapBuffers(window);
        // 检查触发事件
        glfwPollEvents();
    }

    // 删除顶点数组对象以及顶点缓冲对象
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    // 终止退出
    glfwTerminate();
    return 0;
}

void onMouseCallback(GLFWwindow *window, double xpos, double ypos) {
    // 灵敏度 不要太大
    float sensitivity = 0.1f;

    // 第一次移动鼠标赋值
    if (isFirstMouse) {
        lastX = (float) xpos;
        lastY = (float) ypos;
        isFirstMouse = false;
    }

    // 计算相对于上一次的偏移
    // y需要反向，因为鼠标和gl坐标相反
    float xoffset = (float) xpos - lastX;
    float yoffset = lastY - (float) ypos;

    // 更新鼠标位置
    lastX = (float) xpos;
    lastY = (float) ypos;

    // 乘上灵敏度
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // 改变偏航角和俯仰角
    yaw += xoffset;
    pitch += yoffset;

    // 限制俯仰角角度
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // 计算新的方向
    // 注意弧度制
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
    glm::vec3 front;
    front.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));
    // 赋值单位向量后的方向
    cameraFront = glm::normalize(front);

}

void onKeyInput(GLFWwindow *window) {
    float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    // 前进后退
    // 加减方向向量
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    }

    // 左右移动
    // 先求右向量，叉乘求得右向量，然后转单位向量
    // 加减右向量
    glm::vec3 right = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
    right *= cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= right;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += right;
    }

    // 上下移动
    // 直接加减世界上向量
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        cameraPos += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        cameraPos -= glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
    }
}

void onFramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    // GL坐标转换屏幕坐标设置的视口
    glViewport(0, 0, width, height);
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
}

GLuint loadTexture(const char *path) {
    GLuint texture;
    // 生成材质
    glGenTextures(1, &texture);
    // 绑定材质
    glBindTexture(GL_TEXTURE_2D, texture);

    // 加载并生成纹理
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = 3;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        // 生成纹理
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        // 生成mipmap
        glGenerateMipmap(GL_TEXTURE_2D);
        // 设置环绕方式 重复
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // 设置过滤方式 线性
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 释放资源
        stbi_image_free(data);
    } else {
        std::cout << "材质加载失败" << std::endl;
    }
    return texture;
}