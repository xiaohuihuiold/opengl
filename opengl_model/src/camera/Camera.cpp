//
// Created by WIN10 on 2019/10/15.
//

#include "Camera.h"

Camera::Camera(GLfloat width, GLfloat height) {
    this->update();
    this->updateSize(width, height);
}

void Camera::toFront() {
    this->position += speed * glm::normalize(front);
    this->update();
}

void Camera::toBack() {
    this->position -= speed * glm::normalize(front);
    this->update();
}

void Camera::toLeft() {
    // 叉乘获取方向
    glm::vec3 left = glm::normalize(glm::cross(front, up));
    this->position -= speed * left;
    this->update();
}

void Camera::toRight() {
    // 叉乘获取方向
    glm::vec3 left = glm::normalize(glm::cross(front, up));
    this->position += speed * left;
    this->update();
}

void Camera::update() {
    this->view = glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::updateProjection() {
    this->projection = glm::perspective(glm::radians(45.0f), size.x / size.y, 0.1f, 100.0f);
}

void Camera::updateSize(GLfloat width, GLfloat height) {
    this->size = glm::vec2(width, height);
    this->updateProjection();
}

void Camera::updateMouse(GLfloat deltaX, GLfloat deltaY) {
    this->yaw += deltaX * sensitivity;
    this->pitch += deltaY * sensitivity;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    this->updateFront();
}

void Camera::updateFront() {
    this->front.x = glm::cos(glm::radians(this->pitch)) * glm::cos(glm::radians(this->yaw));
    this->front.y = glm::sin(glm::radians(this->pitch));
    this->front.z = glm::cos(glm::radians(this->pitch)) * glm::sin(glm::radians(this->yaw));
    this->update();
}
