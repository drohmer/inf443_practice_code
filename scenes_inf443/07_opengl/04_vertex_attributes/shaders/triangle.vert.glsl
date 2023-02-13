#version 330 core  // OpenGL 3.3

// 2 per-vertex attributes: 
//  - position at location 0
//  - color at location 1
layout (location = 0) in vec3 position; 
layout (location = 1) in vec3 color;

out vec3 color_fragment;

void main()
{
    color_fragment = color; // this variable will be used in the fragment shader

    // Output position (in normalized device coordinates) is directly the position
    gl_Position = vec4(position, 1.0);
}