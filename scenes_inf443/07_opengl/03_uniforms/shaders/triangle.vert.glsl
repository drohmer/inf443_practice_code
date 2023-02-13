#version 330 core

layout (location = 0) in vec3 position;

// This variable must be set in the C++ code before the draw call
uniform vec3 translation;

void main()
{
    vec3 p = position + translation;

    gl_Position = vec4(p, 1.0);
}