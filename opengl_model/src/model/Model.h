//
// Created by WIN10 on 2019/10/17.
//

#ifndef OPENGL_MODEL_MODEL_H
#define OPENGL_MODEL_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../shader/Shader.h"
#include "Mesh.h"

class Model {
public:
    Model(char *path);

    void draw(Shader shader);

private:
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;
    std::string directory;
private:
    void loadModel(std::string path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    GLuint TextureFromFile(const char *path, const std::string &directory, bool gamma);
};


#endif //OPENGL_MODEL_MODEL_H
