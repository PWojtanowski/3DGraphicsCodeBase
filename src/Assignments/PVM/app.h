//
// Created by pbialas on 05.08.2020.
//

#pragma once

#include <vector>

#include "Application/application.h"
#include "Application/utils.h"

#include "glad/gl.h"
#include <glm/glm.hpp>

class SimpleShapeApplication : public xe::Application
{
    GLuint v_buffer_handle;
    GLuint i_buffer_handle;
    GLuint c_buffer_handle;
    GLuint t_buffer_handle;

public:
    SimpleShapeApplication(int width, int height, std::string title, bool debug) : Application(width, height, title, debug) {}

    void init() override;

    void frame() override;

private:
    GLuint vao_;
};