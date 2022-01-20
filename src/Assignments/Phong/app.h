//
// Created by pbialas on 05.08.2020.
//

#pragma once

#include <vector>

#include "Application/application.h"
#include "Application/utils.h"

#include "Engine/Mesh.h"
#include "Engine/Material.h"

#include "glad/gl.h"
#include <glm/glm.hpp>
#include "camera.hpp"
#include "camera_controler.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#include "Application/utils.h"
#include "Engine/mesh_loader.h"

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

    Camera camera_;
    CameraControler controler_{&camera_};

    std::vector <xe::Mesh*> meshes_;

public:
    SimpleShapeApplication(int width, int height, std::string title, bool debug) : Application(width, height, title, debug) {}

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;
    void scroll_callback(double xoffset, double yoffset) override;
    void mouse_button_callback(int button, int action, int mods) override;
    void cursor_position_callback(double x, double y) override;

    void add_submesh(xe::Mesh *mesh);

private:
    GLuint vao_;
};