#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>



namespace xe {
    GLuint create_texture(const std::string &name);
}
#endif