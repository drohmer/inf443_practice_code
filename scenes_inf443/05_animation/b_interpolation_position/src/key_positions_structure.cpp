#include "key_positions_structure.hpp"

using namespace cgp;

void keyframe_structure::initialize(numarray<vec3> const& key_positions_arg, numarray<float> const& key_times_arg)
{
	key_positions = key_positions_arg;
	key_times = key_times_arg;

	// Initialise the mesh_drawable
	sphere_key_positions.initialize_data_on_gpu(mesh_primitive_sphere(0.05f));
	sphere_current.initialize_data_on_gpu(mesh_primitive_sphere(0.06f));
	sphere_key_positions.material.color = { 1,1,1 };
	sphere_current.material.color = { 0,0,1 };

	polygon_key_positions.initialize_data_on_gpu(key_positions);
	polygon_key_positions.color = { 1,0,0 };
}

void keyframe_structure::display_key_positions(environment_structure const& environment)
{
	assert_cgp(key_times.size() == key_positions.size(), "key_time and key_positions should have the same size");

	// Display the key positions
	if (display_keyposition)
	{
		int N = key_positions.size();
		for (int k = 0; k < N; ++k) {
			if (picking.active && picking.index == k)
				sphere_key_positions.material.color = { 1,0,0 };
			else
				sphere_key_positions.material.color = { 1,1,1 };
			sphere_key_positions.model.translation = key_positions[k];
			draw(sphere_key_positions, environment);
		}
	}
		

	// Display the polygon linking the key positions
	if (picking.active)
		polygon_key_positions.vbo_position.update(key_positions); // update the polygon if needed
	if (display_polygon)
		draw(polygon_key_positions, environment);

}

void keyframe_structure::display_current_position(vec3 const& p, environment_structure& environment)
{
	// Display the interpolated position
	sphere_current.model.translation = p;
	draw(sphere_current, environment);

	// Display the trajectory
	trajectory.visual.color = { 0,0,1 };
	trajectory.add(p);
	if (display_trajectory)
		draw(trajectory, environment);
}

void keyframe_structure::update_picking(input_devices const& inputs, camera_generic_base const& camera, camera_projection_perspective const& projection)
{
	// Current position of the mouse
	vec2 const& p = inputs.mouse.position.current;

	// The picking and deformation is only applied when pressing the shift key
	if (inputs.keyboard.shift)
	{
		// If the mouse is not clicked, compute a picking on the vertices of the grid
		if (!inputs.mouse.click.left)
			picking = picking_spheres(p, key_positions, 0.05f, camera, projection);

		// Key position translation
		if (inputs.mouse.click.left && picking.active)
		{
			vec3 new_position = picking_plane_orthogonal_to_camera(p, picking.position, camera, projection).position;
			key_positions[picking.index] = new_position;
		}
	}
	else
		picking.active = false;
}

void keyframe_structure::display_gui()
{
	ImGui::Checkbox("Display key positions", &display_keyposition);
	ImGui::Checkbox("Display polygon", &display_polygon);
	ImGui::Checkbox("Display trajectory", &display_trajectory);
	bool new_size = ImGui::SliderInt("Trajectory size", &trajectory_storage, 2, 500);

	if (new_size) {
		trajectory.clear();
		trajectory = trajectory_drawable(trajectory_storage);
	}
}