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
    // A utility function that reads the shader sources, compiles them and creates the program object
    // As everything in OpenGL we reference program by an integer "handle".
    auto program = xe::utils::create_program(
        {{GL_VERTEX_SHADER, std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
         {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"}});

    if (!program)
    {
        std::cerr << "Invalid program" << std::endl;
        exit(-1);
    }

    std::vector<GLushort> indices = {0,1,2,1,0,3,3,4,0};

    // A vector containing the x,y,z vertex coordinates for the triangle.
    std::vector<GLfloat> vertices = {
         0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f, // 0
        -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f, // 1
         0.0f,  0.5f, 0.0f,  1.0f,  0.0f, 0.0f, // 2
        -0.5f, -0.5f, 0.0f,  0.0f,  1.0f, 0.0f, // 3
         0.5f, -0.5f, 0.0f,  0.0f,  1.0f, 0.0f}; // 4

    GLfloat strength = 0.5;
    GLfloat color[3] = {0.1,1.0,1.0};

    glm::mat4 PVM(1.0f);
    //PVM = glm::rotate(PVM, 1.0f, glm::vec3(0,1,1));

    // Generating the buffer and loading the vertex data into it.
    glGenBuffers(1, &v_buffer_handle);
    OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle));
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &i_buffer_handle);
    OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &c_buffer_handle);
    OGL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, c_buffer_handle));
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER,0,c_buffer_handle);

    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(GLfloat), &strength);
    glBufferSubData(GL_UNIFORM_BUFFER, 4*sizeof(GLfloat), 3*sizeof(GLfloat), color);

    glGenBuffers(1, &t_buffer_handle);
    OGL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, t_buffer_handle));
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &PVM, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER,1,t_buffer_handle);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // This setups a Vertex Array Object (VAO) that  encapsulates
    // the state of all vertex buffers needed for rendering
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, c_buffer_handle);

    // This indicates that the data for attribute 0 should be read from a vertex buffer.
    glEnableVertexAttribArray(0);
    // and this specifies how the data is layout in the buffer.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));

    glEnableVertexAttribArray(1);
    // and this specifies how the data is layout in the buffer.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //end of vao "recording"

    // Setting the background color of the rendering window,
    // I suggest not to use white or black for better debuging.
    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);

    // This setups an OpenGL vieport of the size of the whole rendering window.
    auto [w, h] = frame_buffer_size();
    glViewport(0, 0, w, h);

    glUseProgram(program);
}

//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame()
{
     static auto time = std::chrono::steady_clock::now();
     auto time_n = std::chrono::steady_clock::now();
     std::chrono::duration<double> elapsed = time_n - time;
     time = time_n;
    std::cout<<(1.0f/elapsed.count())<<std::endl;
    
    static float rotation_angle = 0.0f;
    rotation_angle += elapsed.count();

    auto [w, h] = frame_buffer_size();

    glm::mat4 trans(1.0f);    
    trans = glm::perspective(glm::radians(45.0f), (float)w/(float)h, 0.1f, 100.0f);
    trans = glm::translate(trans, glm::vec3(0.0f,0.0f,-2.0f));
    trans = glm::rotate(trans, rotation_angle, glm::vec3(0.0f,1.0f,1.0f));

    glBindBuffer(GL_UNIFORM_BUFFER, t_buffer_handle);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &trans);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* 
        na learnopengl:
        glGetUniformLocation
        glUniformX
    */
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}
