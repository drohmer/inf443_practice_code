#include "interpolation.hpp"


using namespace cgp;

/** Compute the linear interpolation p(t) between p1 at time t1 and p2 at time t2*/
vec3 linear_interpolation(float t, float t1, float t2, vec3 const& p1, vec3 const& p2);

/** Compute the cardinal spline interpolation p(t) with the polygon [p0,p1,p2,p3] at time [t0,t1,t2,t3]
*  - Assume t \in [t1,t2] */
vec3 cardinal_spline_interpolation(float t, float t0, float t1, float t2, float t3, vec3 const& p0, vec3 const& p1, vec3 const& p2, vec3 const& p3, float K);

/** Find the index k such that intervals[k] < t < intervals[k+1] 
* - Assume intervals is a sorted array of N time values
* - Assume t \in [ intervals[0], intervals[N-1] [       */
int find_index_of_interval(float t, buffer<float> const& intervals);


vec3 interpolation(float t, buffer<vec3> const& key_positions, buffer<float> const& key_times)
{
    // Find idx such that key_times[idx] < t < key_times[idx+1]
    int idx = find_index_of_interval(t, key_times);

    // Get parameters (time and position) used to compute the linear interpolation
    //   (You will need to get more parameters for the spline interpolation)
    float t1 = key_times[idx  ]; // = t_i
    float t2 = key_times[idx+1]; // = t_{i+1}

    vec3 const& p1 = key_positions[idx  ]; // = p_i
    vec3 const& p2 = key_positions[idx+1]; // = p_{i+1}
	
    // Call the interpolation
	vec3 p = linear_interpolation(t, t1,t2, p1,p2);

    return p;
}

/** Compute linear interpolation
      t: current time
      k: "current index" such that t_k < t < t_{k+1}, wxith t_k=key_time[k]
      t1: t_k 
      t2: t_{k+1} 
      (p1,p2): positions associated to time (t1,t2) */
vec3 linear_interpolation(float t, float t1, float t2, vec3 const& p1, vec3 const& p2)
{
    float const alpha = (t-t1)/(t2-t1);
    vec3 const p = (1-alpha)*p1 + alpha*p2;

    return p;
}

/** Compute the cardinal spline interpolation
      t: current time
      k: "current index" such that t_k < t < t_{k+1}, wxith t_k=key_time[k]
      t0: t_{k-1}
      t1: t_k
      t2: t_{k+1} 
      t3: t_{k+2}  
      (p0,p1,p2,p3): positions associated to time (t0,t1,t2,t3) 
      K: spline tension       */
vec3 cardinal_spline_interpolation(float t, float t0, float t1, float t2, float t3, vec3 const& p0, vec3 const& p1, vec3 const& p2, vec3 const& p3, float K)
{
    // To do: fill the function to compute p(t) as a cardinal spline interpolation
    vec3 const p = {0,0,0};

    return p;
}

int find_index_of_interval(float t, buffer<float> const& intervals)
{
    int const N = intervals.size();
    bool error = false;

    if (intervals.size() < 2) {
        std::cout<<"Error: Intervals should have at least two values; current size="<<intervals.size()<<std::endl;
        error = true;
    }
    if (N>0 && t < intervals[0]) {
        std::cout<<"Error: current time t is smaller than the first time of the interval"<<std::endl;
        error = true;
    }
    if(N>0 && t > intervals[N-1]) {
        std::cout<<"Error: current time t is greater than the last time of the interval"<<std::endl;
        error = true;
    }
    if (error == true) {
        std::string const error_str = "Error trying to find interval for t="+str(t)+" within values: ["+str(intervals)+"]";
        error_cgp( error_str );
    }


    int k=0;
    while( intervals[k+1]<t )
        ++k;
    return k;
}