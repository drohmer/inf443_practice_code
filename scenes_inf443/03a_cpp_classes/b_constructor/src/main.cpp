#include <iostream>
#include <cmath>


struct vec3 {
    float x, y, z;

    // Constructor (without argument)
    vec3();

    // Constructor with arguments
    vec3(float x, float y);

    // Copy constructor
    vec3(vec3 const& v);

    // Destructor
    ~vec3();

    void display() const;
};

// This is another operator: <<, that is used to be able to write cout<<vec3
std::ostream& operator<<(std::ostream& s, vec3 const& v)
{
    s << "(" << v.x << "," << v.y << "," << v.z << ")";
    return s;
}
void vec3::display() const
{
    std::cout<< "(" << x << "," << y << "," << z << ")";
}

vec3::vec3() {
    std::cout << "> I am the empty constructor. I set everything to 1." << std::endl;

    // This is an unusual construction for a vector
    // only for the sake of learning c++
    x = 1; y = 1; z = 1;
}

vec3::vec3(float x_arg, float y_arg)
{
    std::cout << "> I am the constructor with two argument (" <<x_arg<<", "<<y_arg <<")"<< std::endl;
    x = x_arg;
    y = y_arg;
    z = 0;
}

vec3::~vec3()
{
    std::cout << "> I am the destructor of this vector: ";
    display();
    std::cout << std::endl;
    
    // The destructor is useless in this example
}

vec3::vec3(vec3 const& to_be_copied)
{
    std::cout << "> I am the copy constructor. I am going to copy this vector: ";
    to_be_copied.display();
    std::cout << std::endl;

    x = to_be_copied.x;
    y = to_be_copied.y;
    z = to_be_copied.z+1 ; // this is a very bad idea to do that, but we can do it anywhere!
    // the "copied" version has now (x,y,z+1) as coordinates
}



int main()
{
    vec3 a; // Empty constructor call
    std::cout << "a=" << a << std::endl;

    vec3 b = { 4,7 }; // Constructor with two arguments
    std::cout << "b=" << b << std::endl;

    {
        std::cout << "-- Beginning of block --" << std::endl;

        vec3 c = { 8,1 }; // Constructor with two arguments
        std::cout << "c=" << c << std::endl;

        std::cout << "-- End of block --" << std::endl;    
    } // Call of the destructor on c

    vec3 d = b; // Call of the copy constructor
    std::cout << "d=" << d << std::endl;


    
    return 0; // destroy a and b
}
