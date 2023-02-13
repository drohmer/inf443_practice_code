#include "cgp/cgp.hpp"

/** Helping structure handling the display and interaction with the set of key-frames: key positions + times 
	Note: this structure doesn't perform the interpolation */
struct keyframe_structure {

	// alias on the environment type (only use to shorten the syntax)
	using environmentType = cgp::scene_environment_basic_camera_spherical_coords;

public:

	// Storage of the key positions and times
	//  key_positions and key_times should have the same number of elements
	cgp::buffer<cgp::vec3> key_positions;
	cgp::buffer<float> key_times;


	// This function must be called once at the initialization step.
	//  It sets the positions and times, but also initialize the mesh_drawable elements
	void initialize(cgp::buffer<cgp::vec3> const& key_positions, cgp::buffer<float> const& key_times);
	
	// This function should be called every time the mouse cursor is moved - it handles the interactive drag of positions
	void update_picking(cgp::inputs_interaction_parameters const& inputs, environmentType& environment);

	// Draw all the key positions as well as the polygon linking these positions
	void display_key_positions(environmentType const& environment);

	// Draw the current position and update the trajectory of the particle
	//  p : the position computed after interpolation
	//  time: the corresponding time (used to display the trajectory)
	void display_current_position(cgp::vec3 const& p, environmentType& environment);

	// Draw the GUI elements associated to the keyframe
	void display_gui();

	cgp::trajectory_drawable trajectory;
private:

	cgp::mesh_drawable sphere_key_positions; // spheres used to display the key positions
	cgp::mesh_drawable sphere_current;       // sphere used to display the current interpolated position
	cgp::curve_drawable polygon_key_positions; //
	
	cgp::picking_structure picking;

	// Gui information
	bool display_polygon = true;
	bool display_keyposition = true;
	bool display_trajectory = true;
	int trajectory_storage = 100;


};