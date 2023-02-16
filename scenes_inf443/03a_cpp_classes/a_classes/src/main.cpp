#include <iostream>
#include <cmath>

struct vec3 {
    float x, y, z;
};

int main()
{
    // create an un-initialized vec3
    vec3 p1; 

    // create and initialize vec3
    vec3 p2 = {1.0f, 2.0f, 5.0f}; 

    // Access attributes of the struct
    p2.y = -4.0f;

    std::cout<<p2.x<<","<<p2.y<<","<<p2.z<<std::endl;

    return 0;
}
