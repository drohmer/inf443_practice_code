#version 330 core // Header for OpenGL 3.3


// Inputs coming from the vertex shader
in struct fragment_data
{
    vec3 position; // position in the world space
    vec3 normal;   // normal in the world space
    vec3 color;    // current color on the fragment
    vec2 uv;       // current uv-texture on the fragment

} fragment;

// Output of the fragment shader - output color
layout(location=0) out vec4 FragColor;

// View matrix
uniform mat4 view;

struct material_structure
{
	vec3 color;  // Uniform color of the object
};
uniform material_structure material;

// Ambiant uniform controled from the GUI
uniform float ambiant;
uniform vec3 light_color;
uniform vec3 light_position;

uniform float diffuse;
uniform float specular;
uniform float specular_exp;
uniform vec3 fog_color;

void main()
{
	vec3 current_color;
	//current_color = ambiant * material.color * light_color;
	//FragColor = vec4(current_color, 1.0); 	// Note: the last alpha component is not used here

	
	vec3 L = normalize(light_position - fragment.position);
	vec3 N = normalize(fragment.normal);

	float diffuse_value = max(dot(N, L), 0.0);
	float diffuse_magnitude = diffuse * diffuse_value;
	//current_color = (ambiant + diffuse_magnitude) * material.color * light_color;
	//FragColor = vec4(current_color, 1.0);


	// Compute the position of the center of the camera
	mat3 O = transpose(mat3(view));                   // get the orientation matrix
	vec3 last_col = vec3(view * vec4(0.0, 0.0, 0.0, 1.0)); // get the last column
	vec3 camera_position = -O * last_col;

	// Specular coefficient
	float specular_magnitude = 0.0;
	vec3 u_r = reflect(-L, N); // reflection of light vector relative to the normal.
	vec3 u_v = normalize(camera_position - fragment.position);
	specular_magnitude = specular * pow(max(dot(u_r, u_v), 0.0), specular_exp);

	// Light attenuation
	float d_l = length(light_position - fragment.position);
	float d_lmax = 4.0;
	float alpha_l = min(d_l / d_lmax, 1.0);
	vec3 Cl = (1 - alpha_l) * light_color;

	current_color = (ambiant + diffuse_magnitude) * material.color * Cl + specular_magnitude * Cl;


	float d_max = 12.0;
	float d = length(camera_position - fragment.position);
	float alpha_f = min(d / d_max, 1.0);
	
	current_color = (1 - alpha_f) * current_color + alpha_f*fog_color;

	FragColor = vec4(current_color, 1.0);



}