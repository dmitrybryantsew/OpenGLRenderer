#include "Light.hpp"

Light::Light()
    :color(glm::vec3(1.0f, 1.0f, 1.0f)),
    ambientIntensity(1.0f)
    {

}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
             GLfloat dIntensity) :
                           color(glm::vec3(red, green, blue)),
                           ambientIntensity(aIntensity),
                           diffuseIntensity(dIntensity)
                           {
}

Light::~Light() {

}


