#pragma once


#include "cgp/cgp.hpp"

// Compute the interpolated position p(t) given a time t and the set of key_positions and key_frame
cgp::vec3 interpolation(float t, cgp::numarray<cgp::vec3> const& key_positions, cgp::numarray<float> const& key_times);

