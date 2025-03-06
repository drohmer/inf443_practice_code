#include "scene.hpp"


using namespace cgp;



void scene_structure::initialize()
{
	camera_control.initialize(inputs, window); // Give access to the inputs and window global state to the camera controler
	camera_control.set_rotation_axis_z();
	camera_control.look_at({ 3.0f, 2.0f, 2.0f }, {0,0,0}, {0,0,1});
	global_frame.initialize_data_on_gpu(mesh_primitive_frame());



	camel.initialize_data_on_gpu(mesh_load_file_obj(project::path+"assets/camel.obj"));
	camel.model.translation = { -1.0f, -2.0f, 0.5f };
	camel.model.scaling = 0.5f;

	cube.initialize_data_on_gpu(mesh_primitive_cube());
	cube.model.translation = { -1.0f, 1.5f, 0.0f };

	ground.initialize_data_on_gpu(mesh_primitive_quadrangle({ -10,-10,0 }, { 10,-10,0 }, { 10,10,0 }, { -10,10,0 }));
	ground.model.translation = {0,0,-0.52};

	


	// Shader used to create the depth map
	opengl_shader_structure shader_depth_map; 
	// Shader used to display the shadow on standard meshes
	opengl_shader_structure shader_mesh_with_shadow; 

	// Load the shaders
	shader_depth_map.load(project::path+"shaders/depth_map/depth_map.vert.glsl", project::path+"shaders/depth_map/depth_map.frag.glsl");
	shader_mesh_with_shadow.load(project::path+"shaders/mesh_with_shadow/mesh_with_shadow.vert.glsl", project::path+"shaders/mesh_with_shadow/mesh_with_shadow.frag.glsl");

	// Initialize the shadow mapping structure
	shadow_mapping.initialize(shader_depth_map);


	// Set the shaders to the drawable that can receives shadows
	camel.shader = shader_mesh_with_shadow;
	camel.supplementary_texture["depth_map_texture"] = shadow_mapping.get_depth_map_texture();

	cube.shader = shader_mesh_with_shadow;
	cube.supplementary_texture["depth_map_texture"] = shadow_mapping.get_depth_map_texture();

	ground.shader = shader_mesh_with_shadow;
	ground.supplementary_texture["depth_map_texture"] = shadow_mapping.get_depth_map_texture();

	// Create the light matrix
	view_light = camera_control.camera_model.matrix_view();
	environment.uniform_generic.uniform_mat4["projection_light"] = projection_orthographic(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 30.0f);

}



void scene_structure::display_frame()
{
	// Set the "view matrix" from the light
	environment.uniform_generic.uniform_mat4["view_light"] = view_light;

	// 1st Pass - Draw the scene from the light "point of view" and store the depth map
	// ************************************************************************ //
	shadow_mapping.start_pass_depth_map_creation();

	// Use shadow_mapping.draw_depth_map(drawable, environment) on all shape that emits shadows
	shadow_mapping.draw_depth_map(camel, environment);	
	shadow_mapping.draw_depth_map(cube, environment);
	shadow_mapping.draw_depth_map(ground, environment);
	if (gui.display_frame)
		shadow_mapping.draw_depth_map(global_frame, environment);

	shadow_mapping.end_pass_depth_map_creation();


	// 2nd Pass - Draw the standard scene
	// ************************************************************************ //

	glViewport(0, 0, window.width, window.height);
	glClearColor(1,1,1, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	// Only drawable using the shader_mesh_with_shadow can be affected by the shadow of other elements
	draw(camel, environment);
	draw(cube, environment);
	draw(ground, environment);

	if(gui.display_wireframe) {
		draw_wireframe(camel, environment);
		draw_wireframe(cube, environment);
		draw_wireframe(ground, environment);
	}

	if (gui.display_frame)
		draw(global_frame, environment, 1, 0);



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

