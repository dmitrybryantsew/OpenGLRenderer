#ifndef TEMPLATEPROJECT_AMBIENTLIGHT_HPP
#define TEMPLATEPROJECT_AMBIENTLIGHT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

class AmbientLight {
public:
    AmbientLight();
    AmbientLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity);

    void useLight(GLfloat ambientIntensityLocation, GLfloat colorLocation);

    ~AmbientLight();
private:
    glm::vec3 color;
    GLfloat  ambientIntensity;
};


#endif //TEMPLATEPROJECT_AMBIENTLIGHT_HPP
