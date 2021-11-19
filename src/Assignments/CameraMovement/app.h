//
// Created by pbialas on 05.08.2020.
//

#pragma once

#include <vector>

#include "Application/application.h"
#include "Application/utils.h"

#include "glad/gl.h"
#include <glm/glm.hpp>
#include "camera.hpp"

class SimpleShapeApplication : public xe::Application
{
    GLuint v_buffer_handle;
    GLuint i_buffer_handle;
    GLuint c_buffer_handle;
    GLuint t_buffer_handle;

    float fov_;
    float aspect_;
    float near_;
    float far_; 

    Camera camera;

public:
    SimpleShapeApplication(int width, int height, std::string title, bool debug) : Application(width, height, title, debug) {}

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

    void scroll_callback(double xoffset, double yoffset) override;

private:
    GLuint vao_;
};