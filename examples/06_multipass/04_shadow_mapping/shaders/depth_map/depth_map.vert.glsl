#version 330 core

layout (location = 0) in vec3 vertex_position; // vertex position in local space (x,y,z)


// Uniform variables expected to receive from the C++ program
uniform mat4 model; // Model affine transform matrix associated to the current shape
uniform mat4 view_light;  // View matrix (rigid transform) of the camera
uniform mat4 projection_light; // Projection (perspective or orthogonal) matrix of the camera


void main()
{
    gl_Position = projection_light * view_light * model * vec4(vertex_position, 1.0);
}  
