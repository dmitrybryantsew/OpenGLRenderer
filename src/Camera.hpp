#ifndef TEMPLATEPROJECT_CAMERA_HPP
#define TEMPLATEPROJECT_CAMERA_HPP

#include "stdafx.hpp"
#include <array>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    Camera();
    Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed);
    void keyControl(const std::array<bool, 1024>& keys, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);
    glm::mat4 calculateViewMatrix();
    glm::vec3 getCameraDirection();
    ~Camera();

private:
    glm::vec3 position;
public:
    const glm::vec3 &getPosition() const;

private:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat moveSpeed;
    GLfloat turnSpeed;

    void update();
};


#endif //TEMPLATEPROJECT_CAMERA_HPP
