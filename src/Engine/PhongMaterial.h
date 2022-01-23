#pragma once

#include "Material.h"

namespace xe {
    class PhongMaterial : public Material {
    public: 
        PhongMaterial(const glm::vec4 color) 
            : color_(color), texture_(0), texture_unit_(0) {}

        void bind();

        static void init();

        static GLuint program() { return shader_; }

        void set_texture(GLuint value) {texture_ = value;}
        GLuint get_texture() {return texture_;}
        void set_texture_unit(GLuint value) {texture_unit_ = value;}
        GLuint get_texture_unit() {return texture_unit_;}

    private:
        static GLuint shader_;
        static GLuint color_uniform_buffer_;

        glm::vec4 color_;

        static GLint uniform_map_Kd_location_;
        GLuint texture_;
        GLuint texture_unit_;
    };
}


