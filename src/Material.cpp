#include "Material.hpp"

Material::Material() {}

Material::~Material() {

}

Material::Material(const GLfloat &specularIntensity, const GLfloat &shininess) : specularIntensity(specularIntensity),
                                                                                 shininess(shininess) {

}

void Material::useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation) {
    glUniform1f(specularIntensityLocation, specularIntensity);
    glUniform1f(shininessLocation, shininess);
}
