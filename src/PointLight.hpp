#ifndef TEMPLATEPROJECT_POINTLIGHT_HPP
#define TEMPLATEPROJECT_POINTLIGHT_HPP

#include "Light.hpp"
class PointLight : public Light{
public :
    virtual ~PointLight();
    PointLight();
    PointLight(GLfloat red, GLfloat green, GLfloat blue,
               GLfloat aIntensity, GLfloat dIntensity,
               GLfloat xPos, GLfloat yPos, GLfloat zPos,
               GLfloat con, GLfloat lin, GLfloat exp);

    void useLight(GLuint ambientIntensityLocation, GLuint colorLocation, GLuint diffuseIntensityLocation,
                  GLuint positionLocation, GLuint constantLocation, GLuint linearLocation,
                  GLuint exponentLocation);
    void changePosition(float x, float y, float z);

protected:
    glm::vec3 position;
    GLfloat constant, linear, exponent;
};


#endif //TEMPLATEPROJECT_POINTLIGHT_HPP
