//
// Created by WIN10 on 2019/10/17.
//

#ifndef OPENGL_MODEL_MESH_H
#define OPENGL_MODEL_MESH_H

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include <assimp/types.h>
#include "../shader/Shader.h"

struct Vertex {
    // 顶点位置
    glm::vec3 position;
    // 顶点法向量
    glm::vec3 normal;
    // 顶点纹理贴图坐标
    glm::vec2 texCoord;
};

struct Texture {
    // 纹理id
    GLuint id;
    // 纹理类型
    std::string type;
    aiString path;
};

class Mesh {
public:
    // 顶点数据
    std::vector<Vertex> vertices;
    // 顶点索引数据
    std::vector<GLuint> indices;
    // 纹理数据
    std::vector<Texture> textures;
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

    void draw(Shader shader);

private:
    // 顶点数组,缓冲,索引对象
    GLuint VAO, VBO, EBO;
private:
    void setupMesh();
};


#endif //OPENGL_MODEL_MESH_H
