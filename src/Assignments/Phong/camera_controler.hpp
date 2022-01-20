#ifndef CAMERACONTROLER_H
#define CAMERACONTROLER_H
#pragma once

#include <stdexcept>
#include "camera.hpp"
	
class CameraControler  
{
public:
	CameraControler();
	CameraControler(Camera *camera);
	~CameraControler();

	void set_camera(Camera *camera);
	void rotate_camera(float dx, float dy);
	void mouse_moved(float x, float y);
	void LMB_pressed(float x, float y);
	void LMB_released(float x, float y);
	

private:
	Camera * camera_;
	float scale_ = 0.01f, x_{0.0f}, y_{0.0f};
	bool LMB_pressed_{false};
};
#endif