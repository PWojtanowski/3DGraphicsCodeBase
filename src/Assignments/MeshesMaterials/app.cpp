//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#include "Application/utils.h"

void SimpleShapeApplication::init()
{
    xe::ColorMaterial::init();
    
    std::vector<GLushort> indices = {3,1,0,
                                    2,3,0,
                                    0,4,2,
                                    0,1,4,
                                    1,3,4,
                                    3,2,4};

    // A vector containing the x,y,z vertex coordinates for the triangle.
    std::vector<GLfloat> vertices = {
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        0.0f, 1.0f, 0.0f
        };

    GLfloat strength = 1.0;
    GLfloat color[3] = {1.0,1.0,1.0};

    glm::mat4 PVM(1.0f);
  
    glGenBuffers(1, &t_buffer_handle);
    OGL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, t_buffer_handle));
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &PVM, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER,1,t_buffer_handle);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Setting the background color of the rendering window,
    // I suggest not to use white or black for better debuging.
    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);

    // This setups an OpenGL vieport of the size of the whole rendering window.
   
    auto pyramid = new xe::Mesh(); 
    
    pyramid->allocate_vertex_buffer(vertices.size() * sizeof(GLfloat),  GL_STATIC_DRAW);
    pyramid->load_vertices(0, vertices.size() * sizeof(GLfloat), vertices.data());
    pyramid->vertex_attrib_pointer(0, 3, GL_FLOAT, 3 * sizeof(GLfloat), 0 );
    
    pyramid->allocate_index_buffer(indices.size() * sizeof(GLfloat), GL_STATIC_DRAW);
    pyramid->load_indices(0, indices.size() * sizeof(GLfloat), indices.data());
    pyramid->add_submesh(0,6, new xe::ColorMaterial(glm::vec4(1.0f,0.0f,0.0f,1.0f)));
    pyramid->add_submesh(6,9, new xe::ColorMaterial(glm::vec4(0.0f,1.0f,0.0f,1.0f)));
    pyramid->add_submesh(9,12, new xe::ColorMaterial(glm::vec4(0.0f,0.0f,1.0f,1.0f)));
    pyramid->add_submesh(12,15, new xe::ColorMaterial(glm::vec4(1.0f,0.0f,1.0f,1.0f)));
    pyramid->add_submesh(15,18, new xe::ColorMaterial(glm::vec4(1.0f,1.0f,0.0f,1.0f)));
    add_submesh(pyramid);

    int w, h;
    std::tie(w, h) = frame_buffer_size();
    aspect_ = (float)w/h;
    fov_ = glm::pi<float>()/4.0;
    near_ = 0.1f;
    far_ = 100.0f;

    camera_.look_at(glm::vec3(0.0f, 0.0f, -5.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f));
    
    camera_.perspective(fov_, aspect_, near_, far_);

    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame()
{
    
    //  static auto time = std::chrono::steady_clock::now();
    //  auto time_n = std::chrono::steady_clock::now();
    //  std::chrono::duration<double> elapsed = time_n - time;
    //  time = time_n;
    //std::cout<<(1.0f/elapsed.count())<<std::endl;
    
    // static float rotation_angle = 0.0f;
    // rotation_angle += elapsed.count();

    // auto [w, h] = frame_buffer_size();

    glm::mat4 model(1.0f);   
    //model = glm::rotate(model, rotation_angle, glm::vec3(1.0f,0.0f,1.0f));
    glm::mat4 trans = camera_.projection() * camera_.view() * model;

    glBindBuffer(GL_UNIFORM_BUFFER, t_buffer_handle);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &trans);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    for(auto &m: meshes_)
        m->draw();
    
    // glBindVertexArray(vao_);
    // glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0);
    // glBindVertexArray(0);
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0,0,w,h); 
    aspect_ = (float) w / h;
    camera_.perspective(fov_, aspect_, near_, far_);
}

void SimpleShapeApplication::scroll_callback(double xoffset, double yoffset){
    Application::scroll_callback(xoffset, yoffset);   
    camera_.zoom(-yoffset / 30.0f);
}

void SimpleShapeApplication::mouse_button_callback(int button, int action, int mods) {
    Application::mouse_button_callback(button, action, mods);

    //if (controler_) {
        double x, y;
        glfwGetCursorPos(window_, &x, &y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            controler_.LMB_pressed(x, y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            controler_.LMB_released(x, y);
    //}

}

void SimpleShapeApplication::cursor_position_callback(double x, double y) {
    Application::cursor_position_callback(x, y);
    //if (controler_) {
        controler_.mouse_moved(x, y);
    //}
}

void SimpleShapeApplication::add_submesh(xe::Mesh *mesh){
    meshes_.push_back(mesh);
}