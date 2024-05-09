#pragma once

#include "cgp/cgp.hpp"
#include "../environment.hpp"



// Helper structure to handle shadow mapping
struct shadow_mapping_structure {

	// FBO used to render the depth map
	cgp::opengl_fbo_structure fbo_shadow_map;
	// Texture used to store the depth map
	cgp::opengl_shader_structure shader_depth_map;

	// Initialize the FBO
	void initialize(opengl_shader_structure const& shader_depth_map);

	// Helper functions for the first pass to render the depth map
	void start_pass_depth_map_creation();
	void draw_depth_map(cgp::mesh_drawable drawable, cgp::environment_generic_structure const& environment) const;
	void end_pass_depth_map_creation();
	


	// Shorthand for fbo_shadow_map.texture
	opengl_texture_image_structure get_depth_map_texture() const;
};


