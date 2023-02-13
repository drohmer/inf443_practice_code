#include "scene.hpp"

#include "interpolation.hpp"


using namespace cgp;

void scene_structure::initialize()
{
	// Basic set-up
	// ***************************************** //

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.axis = camera_spherical_coordinates_axis::z;
	environment.camera.look_at({ 0.0f,-2.0f,3.0f }, { 0,0,0 });


	// Definition of the initial data
	//--------------------------------------//

	// Key 3D positions
	buffer<vec3> key_positions = 
	{ {-1,1,0}, {0,1,0}, {1,1,0}, {1,2,0}, {2,2,0}, {2,2,1}, {2,0,1.5}, {1.5,-1,1}, {1.5,-1,0}, {1,-1,0}, {0,-0.5,0}, {-1,-0.5,0} };

	// Key times (time at which the position must pass in the corresponding position)
	buffer<float> key_times = 
	{ 0.0f, 1.0f, 2.0f, 2.5f, 3.0f, 3.5f, 3.75f, 4.5f, 5.0f, 6.0f, 7.0f, 8.0f };

	// Initialize the helping structure to display/interact with these positions
	keyframe.initialize(key_positions, key_times);


	// Set timer bounds
	// The timer must span a time interval on which the interpolation can be conducted
	// By default, set the minimal time to be key_times[1], and the maximal time to be key_time[N-2] (enables cubic interpolation)
	int N = key_times.size();
	timer.t_min = key_times[1];
	timer.t_max = key_times[N - 2];
	timer.t = timer.t_min;

}





void scene_structure::display()
{
	// Basic elements of the scene
	environment.light = environment.camera.position();
	if (gui.display_frame)
		draw(global_frame, environment);

	// Update the current time
	timer.update();
	float t = timer.t;

	// clear trajectory when the timer restart
	if (t < timer.t_min + 0.1f)
		keyframe.trajectory.clear();

	// Display the key positions and lines b/w positions
	keyframe.display_key_positions(environment);

	// Compute the interpolated position
	//  This is this function that you need to complete
	vec3 p = interpolation(t, keyframe.key_positions, keyframe.key_times);

	// Display the interpolated position (and its trajectory)
	keyframe.display_current_position(p, environment);
}




void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);

	ImGui::SliderFloat("Time", &timer.t, timer.t_min, timer.t_max);
	ImGui::SliderFloat("Time scale", &timer.scale, 0.0f, 2.0f);

	// Display the GUI associated to the key position
	keyframe.display_gui();
}

void scene_structure::mouse_move()
{
	// Handle the picking (displacement of the position using mouse drag)
	keyframe.update_picking(inputs, environment);
}
