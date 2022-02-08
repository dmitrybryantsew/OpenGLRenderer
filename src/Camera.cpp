
#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed):
        position(position),
        worldUp(up),
        yaw(yaw),
        pitch(pitch),
        moveSpeed(moveSpeed),
        turnSpeed(turnSpeed)
        {
    update();
}


void Camera::keyControl(const std::array<bool, 1024> &keys, GLfloat deltaTime) {

    GLfloat velocity = moveSpeed * deltaTime;

    if(keys[GLFW_KEY_W])
    {
        position += front * velocity;
    }
    if(keys[GLFW_KEY_S])
    {
        position -= front * velocity;
    }
    if(keys[GLFW_KEY_A])
    {
        position -= right * velocity;
    }
    if(keys[GLFW_KEY_D])
    {
        position += right * velocity;
    }
}

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
Camera::~Camera() {

}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;

    if(pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if(pitch < -89.0f)
    {
        pitch = -89.0f;
    }
    std::cout << yaw << " " << pitch << "\n";
    update();
}

const glm::vec3 &Camera::getPosition() const {
    return position;
}

glm::vec3 Camera::getCameraDirection() {
    return glm::normalize(front);
}

Camera::Camera() {

}


