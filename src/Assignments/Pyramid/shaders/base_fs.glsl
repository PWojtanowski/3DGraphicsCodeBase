#version 420

layout(location=0) out vec4 vFragColor;
layout(location=1) in  vec4 vColor;
layout(std140, binding = 0) uniform Modifier {
    float strength;
    vec3 color;
};

void main() {
    vFragColor = mix(vColor, vec4(color,1.0), 0.5)*strength;
}
