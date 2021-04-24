#ifndef TEMPLATEPROJECT_LIGHT_HPP
#define TEMPLATEPROJECT_LIGHT_HPP
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
class Light {
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
          GLfloat dIntensity);

   virtual ~Light();
protected:
    glm::vec3 color;
    GLfloat  ambientIntensity;
    GLfloat diffuseIntensity;
};


#endif //TEMPLATEPROJECT_LIGHT_HPP
