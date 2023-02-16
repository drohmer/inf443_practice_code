
// To have access to vec3 in this file, we need to include its header
#include "vec3.hpp"
// Note: do not include the implementation file #include "vec3.cpp". It would cause trouble at the end.


int main()
{
	vec3 p = { 1,2,3};
	std::cout <<"p="<< p << std::endl;

	std::cout<<"Norm: "<< norm(p) <<std::endl;
	
	p.normalize();
	std::cout<<"After normalization: "<< p <<std::endl;

	return 0;
}


