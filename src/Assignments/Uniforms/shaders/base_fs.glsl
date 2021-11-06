#version 420

layout(location=0) out vec4 vFragColor;
layout(location=1) in  vec4 color;
layout(std140, binding = 0) uniform Modifier {
    float strength;
    vec4  c; 
};

void main() {
    vFragColor = c;
}
