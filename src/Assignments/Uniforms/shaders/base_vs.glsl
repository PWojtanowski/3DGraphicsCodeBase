#version 420

layout(location=0) in  vec4 a_vertex_position;
layout(location=1) in  vec4 a_vertex_color;
out vec4 vColor;

layout(std140, binding=1) uniform Transformations {
    vec2 scale;
    vec2 translation;
    mat2 rotation;
};

void main() {
    vec4 pos = a_vertex_position;
    pos.xy = rotation * pos.xy;
    pos.x *= scale.x;
    pos.y *= scale.y;
    pos.x += translation.x;
    pos.y += translation.y;
    gl_Position = pos;
    vColor = a_vertex_color;
}
