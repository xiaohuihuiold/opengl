//
// Created by WIN10 on 2019/10/15.
//

#ifndef OPENGL_MODEL_CAMERA_H
#define OPENGL_MODEL_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

class Camera {
public:
    Camera(GLfloat width, GLfloat height);

    void toFront();

    void toBack();

    void toLeft();

    void toRight();

    void updateSize(GLfloat width, GLfloat height);

    void updateMouse(GLfloat deltaX, GLfloat deltaY);

private:
    void update();

    void updateProjection();

    void updateFront();

public:
    // 移动速度
    GLfloat speed = 0.05f;
    // 鼠标灵敏度
    GLfloat sensitivity = 0.1f;
    // 窗口大小
    glm::vec2 size = glm::vec2();
    // 俯仰角
    GLfloat pitch;
    // 偏航角
    GLfloat yaw;
    // 视图
    glm::mat4 view = glm::mat4(1.0f);
    // 投影
    glm::mat4 projection = glm::mat4(1.0f);
    // 相机位置
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    // 相机朝向
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    // 相机上方向
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
};


#endif //OPENGL_MODEL_CAMERA_H
