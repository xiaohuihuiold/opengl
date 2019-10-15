//
// Created by WIN10 on 2019/10/15.
//

#ifndef OPENGL_MODEL_UTIL_H
#define OPENGL_MODEL_UTIL_H

#include <glad/glad.h>
#include "../stb_image/stb_image.h"

GLuint loadImage(const char *path) {
    // 创建并绑定texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // 加载图片并获取宽高通道信息
    int width;
    int height;
    int nrChannel;
    stbi_set_flip_vertically_on_load(true);
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

#endif //OPENGL_MODEL_UTIL_H
