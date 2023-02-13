#version 330 core  // OpenGL 3.3

// Input interpolated from the vertex shader
in vec3 color_fragment;

// The output variable of the fragment is the color (R,G,B,A)
out vec4 FragColor;

void main()
{
    FragColor = vec4(color_fragment, 1.0);
}