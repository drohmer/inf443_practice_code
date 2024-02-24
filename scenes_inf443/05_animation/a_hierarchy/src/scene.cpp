#include "scene.hpp"



using namespace cgp;

void scene_structure::initialize()
{
	// Basic set-up
	// ***************************************** //
	camera_control.initialize(inputs, window); // Give access to the inputs and window global state to the camera controler
	camera_control.set_rotation_axis_z();
	camera_control.look_at({ 2.0f,-2.0f,1.0f }, { 0,0,0 });

	display_info();
	global_frame.initialize_data_on_gpu(mesh_primitive_frame());


	// Create the hierarchy
	// ************************************ //

	// Initialize the temporary mesh_drawable that will be inserted in the hierarchy
	mesh_drawable cube_base;
	mesh_drawable cylinder_base;
	mesh_drawable sphere_junction;
	mesh_drawable cylinder1;
	mesh_drawable cube1;
	mesh_drawable cylinder1_son;

	// Create the geometry of the meshes
	//   Note: this geometry must be set in their local coordinates with respect to their position in the hierarchy (and with respect to their animation)
	cube_base.initialize_data_on_gpu(mesh_primitive_cube()); cube_base.model.scaling = 0.15f;
	cylinder_base.initialize_data_on_gpu(mesh_primitive_cylinder(0.05f, { 0,0,0 }, { 0,0,0.5f }));
	sphere_junction.initialize_data_on_gpu(mesh_primitive_sphere(0.1f));
	cylinder1.initialize_data_on_gpu(mesh_primitive_cylinder(0.05f, { 0,0,0 }, { 1.0f,0,0 }));
	cube1.initialize_data_on_gpu(mesh_primitive_cube()); cube1.model.scaling = 0.15f;
	cylinder1_son.initialize_data_on_gpu(mesh_primitive_cylinder(0.03f, { 0,0,-0.25f }, { 0.0f,0,0.25f }));

	// Set the color of some elements
	vec3 color1 = { 0.8f, 0.5f, 0.7f };
	cylinder1.material.color = color1;
	cube1.material.color = color1;
	cylinder1.material.color = color1;
	cylinder1_son.material.color = color1;


	// Add the elements in the hierarchy
	//   The syntax is hierarchy.add(mesh_drawable, "name of the parent element", [optional: local translation in the hierarchy])
	//   Notes: 
	//     - An element must necessarily be added after its parent
	//     - The first element (without explicit name of its parent) is assumed to be the root.
	hierarchy.add(cube_base, "Cube base");
	hierarchy.add(cylinder_base, "Cylinder base", "Cube base");
	hierarchy.add(sphere_junction, "Sphere junction", "Cylinder base", {0,0,0.5f}); // the translation is used to place the sphere at the extremity of the cylinder
	hierarchy.add(cylinder1, "Cylinder1", "Sphere junction");
	hierarchy.add(cube1, "Cube1", "Cylinder1", {1.0f,0,0}); // the translation is used to place the cube at the extremity of the cylinder
	hierarchy.add(cylinder1_son, "Cylinder1 son", "Cube1");


}





void scene_structure::display_frame()
{
	// Set the light to the current position of the camera
	environment.light = camera_control.camera_model.position();
	if (gui.display_frame)
		draw(global_frame, environment);

	// Update the current time
	timer.update();

	// Apply transformation to some elements of the hierarchy
	hierarchy["Cylinder1"].transform_local.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, timer.t);
	hierarchy["Cube1"].transform_local.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -3 * timer.t);


	// This function must be called before the drawing in order to propagate the deformations through the hierarchy
	hierarchy.update_local_to_global_coordinates();

	// Draw the hierarchy as a single mesh
	draw(hierarchy, environment);
	if (gui.display_wireframe)
		draw_wireframe(hierarchy, environment);

}




void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);

}

void scene_structure::mouse_move_event()
{
	if (!inputs.keyboard.shift)
		camera_control.action_mouse_move(environment.camera_view);
}
void scene_structure::mouse_click_event()
{
	camera_control.action_mouse_click(environment.camera_view);
}
void scene_structure::keyboard_event()
{
	camera_control.action_keyboard(environment.camera_view);
}
void scene_structure::idle_frame()
{
	camera_control.idle_frame(environment.camera_view);
}

void scene_structure::display_info()
{
	std::cout << "\nCAMERA CONTROL:" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << camera_control.doc_usage() << std::endl;
	std::cout << "-----------------------------------------------\n" << std::endl;
}