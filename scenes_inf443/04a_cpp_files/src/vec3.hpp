#pragma once // This line ensure that we won't have multiple inclusion of this file

#include <iostream>
#include <cmath>

// This is a header file.
// It contains struct/class declaration, as well as header of functions that can be used in code including this file.

// Struct declaration
struct vec3 {
    float x, y, z;

    // Normalize the current vec3
    void normalize();
};

// Function declaration
// Compute the norm of a vec3 
float norm(vec3 const& v);

// Another function declaration (operator <<)
std::ostream& operator<<(std::ostream& s, vec3 const& v);

// The code corresponding to the implementation of the method and functions are in vec3.cpp