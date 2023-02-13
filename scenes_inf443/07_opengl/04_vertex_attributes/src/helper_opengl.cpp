#include "helper_opengl.hpp"

#include <fstream>
#include <sstream>
#include <vector>

std::string read_text_file(std::string const& filename)
{

    std::ifstream str(filename);

    if (str.good() == false) {
        std::cout << "Cannot read file " << filename << std::endl;
        abort();
    }

    std::stringstream buffer;
    buffer << str.rdbuf();
    return buffer.str();
}

static bool check_compilation(GLuint shader)
{
    GLint is_compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);

    // get info on compilation
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(static_cast<size_t>(maxLength) + 1);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

    if (maxLength >= 1)
    {
        std::cout << "[Info from shader compilation]" << std::endl;
        std::cout << &infoLog[0] << std::endl;
    }

    if (is_compiled == GL_FALSE)
    {
        std::cout << "Compilation Failed" << std::endl;
        glDeleteShader(shader);
        return false;
    }
    return true;
}

static bool check_link(GLuint vertex_shader, GLuint fragment_shader, GLuint program)
{
    GLint is_linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &is_linked);

    // Get info on Link
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(static_cast<size_t>(maxLength) + 1);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    if (maxLength >= 1)
    {
        std::cout << "[Info from shader Link]" << std::endl;
        std::cout << &infoLog[0] << std::endl;
    }
    if (is_linked == GL_FALSE) //if failed link
    {
        // clean memory
        glDeleteProgram(program);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        std::cout << "Failed to link shader program" << std::endl;
        return false;
    }
    return true;

}

static bool compile_shader(const GLenum shader_type, std::string const& shader_str, GLuint& shader_id)
{
    shader_id = glCreateShader(shader_type);

    char const* const shader_cstring = shader_str.c_str();
    glShaderSource(shader_id, 1, &shader_cstring, nullptr);

    // Compile shader
    glCompileShader(shader_id);

    bool valid = check_compilation(shader_id);
    return valid;
}


GLuint opengl_load_shader(std::string const& vertex_shader_path, std::string const& fragment_shader_path)
{

    // Read the files
    std::string const vertex_shader_text = read_text_file(vertex_shader_path);
    std::string const fragment_shader_text = read_text_file(fragment_shader_path);


    // Compile the shaders
    GLuint vertex_shader_id = 0;
    GLuint fragment_shader_id = 0;

    bool const vertex_shader_valid   = compile_shader(GL_VERTEX_SHADER, vertex_shader_text, vertex_shader_id);
    bool const fragment_shader_valid = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_text, fragment_shader_id);


    // Error display
    if (vertex_shader_valid == false) {
        std::cout << "===> Failed to compile the Vertex Shader [" << vertex_shader_path << "]" << std::endl;
        std::cout << "The error message from the compiler should be listed above. The program will stop." << std::endl;
        abort();
    }
    
    if (fragment_shader_valid == false) {
        std::cout << "===> Failed to compile the Fragment Shader [" << fragment_shader_path << "]" << std::endl;
        std::cout << "The error message from the compiler should be listed above. The program will stop." << std::endl;
        abort();
    }




    // Create Program
    GLuint const program_id = glCreateProgram();

    // Attach Shader to Program
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    // Link Program
    glLinkProgram(program_id);
    bool const shader_program_valid = check_link(vertex_shader_id, fragment_shader_id, program_id);
    if (shader_program_valid == false) {
        std::cout << "Failed to link the shaders into a fragment program with the following shaders [" << vertex_shader_path << "," << fragment_shader_path << "]" << std::endl;
        abort();
    }


    // Shader can be detached.
    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);


    // Debug info
    std::cout << "\n[info] Shader compiled succesfully [ID = " << program_id<<"]"<< std::endl;
    std::cout << "\t ("<<vertex_shader_path<<", "<<fragment_shader_path<<")" << std::endl;

    return program_id;
}