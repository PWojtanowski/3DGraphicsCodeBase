#version 460

layout(location=0) out vec4 vFragColor;

#if __VERSION__ > 410
layout(std140, binding=0) uniform Modifiers {
#else
    layout(std140) uniform Color {
    #endif
    vec4  Kd;
    bool use_map_Kd;
};

in vec2 vertex_texcoords;
in vec3 vertex_normals_in_vs;
in vec4 vertex_coords_in_vs;

uniform sampler2D map_Kd;

const int MAX_POINT_LIGHTS=24;

struct PointLight {
    vec3 position_in_view_space;
    vec3 color;
    float intensity;
    float radius;
} ;  

layout(std140, binding=2) uniform Lights {
    vec3 ambient;
    uint n_p_lights;
    PointLight p_light[MAX_POINT_LIGHTS];
};

void main() {

    vec3 normal = normalize(vertex_normals_in_vs.xyz);
    vec3 result_difuse = vec3(0,0,0);
    for(uint i =0; i<n_p_lights; ++i){
        vec3 light_vec = vec3(vertex_coords_in_vs) - p_light[i].position_in_view_space;
        float llen = length(light_vec);
        vec3 diffuse =  (llen < p_light[i].radius)? p_light[i].color : vec3(0,0,0);
        float d = dot(normalize(light_vec), normal);
        result_difuse += d* diffuse;
    }

    vec4 ac = vec4(ambient, 1.0);
    vec4 dc = vec4(result_difuse, 0.0); 
    
    if (use_map_Kd)
        vFragColor = (ac+dc) *texture(map_Kd, vertex_texcoords);
        
    else
        vFragColor = Kd;

    //vFragColor.rgb = normal;
    //vFragColor = abs(vertex_coords_in_vs);
}