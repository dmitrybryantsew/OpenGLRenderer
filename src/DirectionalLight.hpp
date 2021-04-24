#ifndef TEMPLATEPROJECT_DIRECTIONALLIGHT_HPP
#define TEMPLATEPROJECT_DIRECTIONALLIGHT_HPP
#include "Light.hpp"

class DirectionalLight : public Light{


public:

    virtual ~DirectionalLight();
    DirectionalLight();
    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
            GLfloat xDir, GLfloat yDir, GLfloat zDir);

    void useLight(GLuint ambientIntensityLocation, GLuint colorLocation,
                  GLuint diffuseIntensityLocation, GLuint directionLocation);

private:
    glm::vec3 direction;
};


#endif //TEMPLATEPROJECT_DIRECTIONALLIGHT_HPP
