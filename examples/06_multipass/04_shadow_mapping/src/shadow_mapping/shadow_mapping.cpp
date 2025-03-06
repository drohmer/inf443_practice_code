#include "shadow_mapping.hpp"

using namespace cgp;

void shadow_mapping_structure::initialize(opengl_shader_structure const& shader_depth_map_arg)
{
	// Resolution of the shadow map
	fbo_shadow_map.width = 2048;
	fbo_shadow_map.height = 2048;

	// Set the FBO to only stores a depth map
	fbo_shadow_map.mode = opengl_fbo_mode::depth;

	// Create the FBO
	fbo_shadow_map.initialize();

	// Store the shader
	shader_depth_map = shader_depth_map_arg;
}

opengl_texture_image_structure shadow_mapping_structure::get_depth_map_texture() const
{
	return fbo_shadow_map.texture;
}

void shadow_mapping_structure::start_pass_depth_map_creation()
{
	glViewport(0, 0, fbo_shadow_map.width, fbo_shadow_map.height);
	fbo_shadow_map.bind();
	glClear(GL_DEPTH_BUFFER_BIT);
}
void shadow_mapping_structure::end_pass_depth_map_creation()
{
	fbo_shadow_map.unbind();
}


void shadow_mapping_structure::draw_depth_map(cgp::mesh_drawable drawable, cgp::environment_generic_structure const& environment) const
{
	drawable.shader = shader_depth_map;
	draw(drawable, environment, 1, 0);
}

