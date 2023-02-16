
// This is an implementation file corresponding to the implementation of the vec3 structure

// We must first include the header file so that we have access in the following to the declared structure and functions
#include "vec3.hpp"

// We can have other includes if necessary
#include <cmath>



// implementation of the method normalize
void vec3::normalize() {
    float n = norm(*this);  // here we use the function norm on the current objet (*this)
    x /= n;
    y /= n;
    z /= n;
}

// implementation of the function norm
float norm(vec3 const& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// implementation of the operator allowing cout<<vec3
std::ostream& operator<<(std::ostream& s, vec3 const& v)
{
    s << "(" << v.x << "," << v.y << "," << v.z << ")";
    return s;
}


// Note: the implementation can be defined in arbitrary order