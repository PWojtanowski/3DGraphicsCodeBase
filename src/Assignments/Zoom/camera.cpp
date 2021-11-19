#include "camera.hpp"

Camera::Camera(){}

void Camera::look_at(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up)
{
    V_ = glm::lookAt(eye, center, up);
}

void Camera::perspective(float fov, float aspect, float near, float far)
{
    fov_ = fov;
    aspect_ = aspect;
    near_ = near;
    far_ = far;

    P_ = glm::perspective(fov_, aspect_, near_, far_);
}

void Camera::set_aspect(float aspect)
{
    aspect_ = aspect;
}

glm::mat4 Camera::view() const { return V_; }
glm::mat4 Camera::projection() const { return P_; }

float inverse_logistic(float x) {
    return std::log(x/(1.0f-x)); 
}

float logistic(float y) {
    return 1.0f/(1.0f+std::exp(-y));
}

void Camera::zoom(float y_offset) {
    auto x = fov_/glm::pi<float>();
    auto y = inverse_logistic(x);
    y+=y_offset;
    x = logistic(y);
    fov_ = x*glm::pi<float>();

    P_ = glm::perspective(fov_, aspect_, near_, far_);
}
