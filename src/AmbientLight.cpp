#include "AmbientLight.hpp"

AmbientLight::AmbientLight()
    :color(glm::vec3(1.0f, 1.0f, 1.0f)),
    ambientIntensity(1.0f)

    {

}

AmbientLight::AmbientLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity) :
                           color(glm::vec3(1.0f, 1.0f, 1.0f)),
                           ambientIntensity(aIntensity)

                           {


}

void AmbientLight::useLight(GLfloat ambientIntensityLocation,
                            GLfloat colorLocation) {
    glUniform3f(colorLocation, color.x, color.y, color.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);


}

AmbientLight::~AmbientLight() {

}


