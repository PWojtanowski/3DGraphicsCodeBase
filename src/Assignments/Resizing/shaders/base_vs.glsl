#version 420

layout(location=0) in  vec4 a_vertex_position;
layout(location=1) in  vec4 a_vertex_color;
out vec4 vColor;

layout(std140, binding=1) uniform Transformations {
    mat4 PVM;
};

void main() {
    vec4 pos = a_vertex_position;
    gl_Position = PVM * pos;
    vColor = a_vertex_color;
}
