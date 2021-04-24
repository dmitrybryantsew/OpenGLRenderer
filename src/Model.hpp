#ifndef TEMPLATEPROJECT_MODEL_HPP
#define TEMPLATEPROJECT_MODEL_HPP
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <boost/algorithm/string.hpp>

#include "Mesh.hpp"
#include "Texture.hpp"

class Model {

public:
    Model();

    void loadModel(const std::string& fileName);
    void renderModel();
    void clearModel();

    ~Model();

private:
    void loadNode(aiNode *node, const aiScene *scene);
    void loadMesh(aiMesh *mesh, const aiScene *scene);
    void loadMaterials(const aiScene *scene);
    std::vector<Mesh*> meshList;
    std::vector<Texture*> textureList;
    std::vector<unsigned  int> meshToTex;
};


#endif //TEMPLATEPROJECT_MODEL_HPP
