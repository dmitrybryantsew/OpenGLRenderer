#ifndef TEMPLATEPROJECT_TEXTURE_HPP
#define TEMPLATEPROJECT_TEXTURE_HPP

#include "stdafx.hpp"
#include <GL/glew.h>
#include <string>
#include <iostream>
#include "stb_image.h"

class Texture {
public:
    Texture();
    Texture(const std::string& filePath);


    bool loadTexture();
    bool loadTextureA();

    void useTexture();
    void clearTexture();

    ~Texture();
private:
    GLuint textureID;
    int width, height, bitDepth;
    std::string filePath;
};


#endif //TEMPLATEPROJECT_TEXTURE_HPP
