#version 330

// Homogeneous variables
uniform mat4 P;                 // perspective matrix
uniform mat4 V;                 // view matrix (observer)
uniform mat4 V_Scene;           // view matrix (scene)
uniform mat4 M;                 // model maxtrix
uniform vec4 light_pos[2];      // lights positions

// attributes
in vec4 vertex;                 // vectex coordinates
in vec4 normal;                 // vertex normal
in vec2 texCoord0;              // vertex coordinates on the texture

// interpolated variables
out vec2 texCoord;              // vertex coordinates on the texture

out vec4 n;                     // normalized normal vector
out vec4 l[2];                  // normalized vectors in the direction of lights
out vec4 v;                     // normalized vector in the direction of observer


void main(void) {
    l[0] = normalize(V_Scene * light_pos[0] - V_Scene * M * vertex);
    l[1] = normalize(V_Scene * light_pos[1] - V_Scene * M * vertex);
    v = normalize(vec4(0, 0, 0, 1) - V_Scene * M * vertex);
    n = normalize(V_Scene * M * normal);

    texCoord = texCoord0;

    gl_Position = P * V * M * vertex;
}