#include "tree.hpp"

using namespace cgp;


mesh create_cylinder_mesh(float radius, float height)
{
    mesh m; 
    // To do: fill this mesh ...
    // ...
    // To add a position: 
    //   m.position.push_back(vec3{x,y,z})
    // Or in pre-allocating the buffer:
    //   m.position.resize(maximalSize);
    //   m.position[index] = vec3{x,y,z}; (with 0<= index < maximalSize)
    // 
    // Similar with the triangle connectivity:
    //  m.connectivity.push_back(uint3{index_1, index_2, index_3});


    // Need to call fill_empty_field() before returning the mesh 
    //  this function fill all empty buffer with default values (ex. normals, colors, etc).
    m.fill_empty_field();

    return m;
}

mesh create_cone_mesh(float radius, float height, float z_offset)
{
    mesh m; 
    // To do: fill this mesh ...
    // ...

    m.fill_empty_field();
    return m;
}


