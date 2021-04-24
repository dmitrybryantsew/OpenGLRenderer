#ifndef TEMPLATEPROJECT_SPOTLIGHT_HPP
#define TEMPLATEPROJECT_SPOTLIGHT_HPP

#include <iostream>
#include "PointLight.hpp"

class SpotLight : public PointLight{
public:
    virtual ~SpotLight();
    SpotLight();
    SpotLight(GLfloat red, GLfloat green, GLfloat blue,
    GLfloat aIntensity, GLfloat dIntensity,
    GLfloat xPos, GLfloat yPos, GLfloat zPos,
            GLfloat xDir, GLfloat yDir, GLfloat zDir,
            GLfloat con, GLfloat lin, GLfloat exp, GLfloat edge);

    void useLight(GLuint ambientIntensityLocation, GLuint colorLocation, GLuint diffuseIntensityLocation,
                  GLuint positionLocation, GLuint constantLocation, GLuint linearLocation,
                  GLuint exponentLocation, GLuint directionLocation, GLuint edgeLocation);

    void setFlashlightPosition(glm::vec3 pos, glm::vec3 dir);
private:
    glm::vec3 direction;
    GLfloat edge, processedEdge;
};


#endif //TEMPLATEPROJECT_SPOTLIGHT_HPP
