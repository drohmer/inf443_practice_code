#pragma once

#include "cgp/cgp.hpp"


cgp::mesh create_cylinder_mesh(float radius, float height);
cgp::mesh create_cone_mesh(float radius, float height, float z_offset);

