#ifndef TEMPLATEPROJECT_MATERIAL_HPP
#define TEMPLATEPROJECT_MATERIAL_HPP
#include "stdafx.hpp"
#include <GL/glew.h>
#include <GL/gl.h>


class Material {
public:
    Material();

    Material(const GLfloat &specularIntensity, const GLfloat &shininess);
    void useMaterial(GLuint specularIntensityLocation , GLuint shininessLocation);
    ~Material();
private:
    GLfloat specularIntensity; // reflectiveness of the object
    GLfloat shininess;
};


#endif //TEMPLATEPROJECT_MATERIAL_HPP
