#ifndef CAMERA_H
#define CAMERA_H
#pragma once
#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "rotation.h"

class Camera
{
private:
	float fov_;
	float aspect_;
	float near_;
	float far_;

	//glm::mat4 V_;
	glm::mat4 P_;

	glm::vec3 position_{0.0f}, 
		center_{0.0f}, 
		x_{0.0f},
		y_{0.0f},
		z_{0.0f};

public:
	Camera();
	void look_at(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);
	void perspective(float fov, float aspect, float near, float far);
	void set_aspect(float aspect);
	glm::mat4 view() const;
	glm::mat4 projection() const;
	void zoom(float y_offset);
	void rotate_around_point(float angle, const glm::vec3 &axis, const glm::vec3 &c);
	void rotate_around_center(float angle, const glm::vec3 &axis);

	glm::vec3 x() const { return x_; }
	glm::vec3 y() const { return y_; }
	glm::vec3 z() const { return z_; }
	glm::vec3 position() const { return position_; }
	glm::vec3 center() const { return center_; }
};
#endif