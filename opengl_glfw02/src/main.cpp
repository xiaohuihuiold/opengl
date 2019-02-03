#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WINDOW_TITLE "OpenGL Light"

int WINDOW_WIDTH = 1200;
int WINDOW_HEIGHT = 720;

GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
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

    // 保存着色器状态和编译信息
    GLint success;
    GLchar info[512];

    // 顶点着色器字符串
    std::string vertexStr;
    std::ifstream vertexFile;
    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // 打开文件
        vertexFile.open("../assets/vertex.glsl");
        // 字符流
        std::stringstream vertexStream;
        // 把文件缓冲写入字符流
        vertexStream << vertexFile.rdbuf();
        // 关闭文件流释放资源
        vertexFile.close();
        // 字符流取得字符串
        vertexStr = vertexStream.str();
    } catch (std::ifstream::failure &e) {
        std::cout << "打开顶点着色器错误:" << e.what() << std::endl;
        glfwTerminate();
        return -1;
    }
    // 顶点着色器
    const char *vertexShaderSource = vertexStr.c_str();
    GLuint vertexShader;
    // 创建着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 设置着色器源码
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // 编译着色器
    glCompileShader(vertexShader);
    // 获取着色器编译状态
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // 编译失败就打印信息并终止程序
        glGetShaderInfoLog(vertexShader, 512, nullptr, info);
        std::cout << "顶点着色器编译错误:" << info << std::endl;
        glfwTerminate();
        return -1;
    }

    std::string fragmentStr;
    std::ifstream fragmentFile;
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        std::stringstream fragmentStream;
        fragmentFile.open("../assets/fragment.glsl");
        fragmentStream << fragmentFile.rdbuf();
        fragmentFile.close();
        fragmentStr = fragmentStream.str();
    } catch (std::ifstream::failure &e) {
        std::cout << "读取片元着色器错误:" << e.what() << std::endl;
        glfwTerminate();
        return -1;
    }

    // 片元着色器
    const char *fragmentShaderSource = fragmentStr.c_str();
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, info);
        std::cout << "片元着色器编译错误:" << info << std::endl;
        glfwTerminate();
        return -1;
    }

    // 着色器程序
    GLuint shaderProgram;
    // 创建着色器程序
    shaderProgram = glCreateProgram();
    // 添加顶点着色器
    glAttachShader(shaderProgram, vertexShader);
    // 添加片元着色器
    glAttachShader(shaderProgram, fragmentShader);
    // 链接程序
    glLinkProgram(shaderProgram);

    // 检查程序链接状态
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        // 链接出错就打印信息并终止程序
        glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
        glfwTerminate();
        return -1;
    }

    // 链接成功后删除顶点着色器和片元着色器节省资源
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 生成顶点数组对象,顶点缓冲对象
    GLuint VBO, VAO;
    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 复制到缓冲的内存中
    // GL_ARRAY_BUFFER：目标缓冲类型
    // sizeof(vertices)：传输的数据大小
    // vertices：发送的数据
    // GL_STATIC_DRAW：数据几乎不会改变
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 0: 在顶点着色器中的location
    // 3: 顶点属性大小
    // GL_FLOAT：指定数据类型
    // GL_FALSE：是否标准化
    // 3*sizeof(float)：下一个元素需要跳过的步长
    // (void*)0：数据偏移
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    // 启用下标0的顶点数组参数
    glEnableVertexAttribArray(0);

    // 查找着色器里面变量地址
    GLint modelLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
    GLint projLoc = glGetUniformLocation(shaderProgram, "projMatrix");

    // 初始化相机位置以及朝向
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    // 模型矩阵
    glm::mat4 model = glm::mat4(1.0f);
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

    // 检查是否被要求退出
    while (!glfwWindowShouldClose(window)) {
        // 计算上一祯绘制时间
        deltaTime = (float) glfwGetTime() - lastTime;
        lastTime = (float) glfwGetTime();

        // 每帧开始处理键盘输入
        onKeyInput(window);

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
        proj = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清除颜色缓冲，清除深度缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);

        // 把模型，观察，投影矩阵传递到着色器
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        // 绑定顶点数组
        glBindVertexArray(VAO);
        // 绘制三角形数组
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // 交换颜色缓冲，绘制
        glfwSwapBuffers(window);
        // 检查触发事件
        glfwPollEvents();
    }

    // 删除顶点数组对象以及顶点缓冲对象
    glDeleteVertexArrays(1, &VAO);
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