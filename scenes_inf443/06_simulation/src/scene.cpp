#include "scene.hpp"


using namespace cgp;


// Spring force applied on particle p_i with respect to position p_j.
vec3 spring_force(vec3 const& p_i, vec3 const& p_j, float L0, float K)
{
	vec3 const p = p_i - p_j;
	float const L = norm(p);
	vec3 const u = p / L;

	vec3 const F = -K * (L - L0) * u;
	return F;
}


void scene_structure::simulation_step(float dt)
{
	// Simulation parameters
	float m = 0.01f;       // particle mass
	float K = 5.0f;        // spring stiffness
	float mu = 0.01f;      // damping coefficient

	vec3 g = { 0,0,-9.81f }; // gravity



	// Forces
	vec3 fB_spring = spring_force(pB, pA, L0, K);
	vec3 fB_weight = m * g;
	vec3 fB_damping = -mu * vB;
	vec3 fB = fB_spring + fB_weight + fB_damping;

	// Numerical Integration
	vB = vB + dt * fB / m;
	pB = pB + dt * vB;



}


void scene_structure::draw_segment(vec3 const& a, vec3 const& b)
{
	segment.vbo_position.update(numarray<vec3>{ a, b });
	draw(segment, environment);
}

void scene_structure::initialize()
{
	camera_control.initialize(inputs, window); // Give access to the inputs and window global state to the camera controler
	camera_control.set_rotation_axis_z();
	camera_control.look_at({ 3.0f, 2.0f, 2.0f }, { 0,0,0 }, { 0,0,1 });

	display_info();
	global_frame.initialize_data_on_gpu(mesh_primitive_frame());


	// Initial position and speed of particles
	// ******************************************* //
	pA = { 0,0,0 };
	vB = { 0,0,0 };

	pB = { 0.0f,0.45f,0.0f };
	vB = { 0,0,0 };

	L0 = 0.4f;

	particle_sphere.initialize_data_on_gpu(mesh_primitive_sphere(0.05f));
	segment.display_type = curve_drawable_display_type::Segments;
	segment.initialize_data_on_gpu({ {0,0,0},{1,0,0} });



}






void scene_structure::display_frame()
{
	// Set the light to the current position of the camera
	environment.light = camera_control.camera_model.position();
	
	if (gui.display_frame)
		draw(global_frame, environment);

	// Update the current time
	timer.update();


	simulation_step(timer.scale * 0.01f);

	particle_sphere.model.translation = pA;
	particle_sphere.material.color = { 0,0,0 };
	draw(particle_sphere, environment);

	particle_sphere.model.translation = pB;
	particle_sphere.material.color = { 1,0,0 };
	draw(particle_sphere, environment);

	draw_segment(pA, pB);

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