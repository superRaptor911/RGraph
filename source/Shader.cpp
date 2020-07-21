#include <RG/Shader.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


using namespace rg;

Shader::Shader()
{
    _ref_count = new int;
    *_ref_count = 1;
}

Shader::Shader(const Shader &shader)
{
    _ref_count = shader._ref_count;
    *_ref_count += 1;

    _vertex_shader = shader._vertex_shader;
    _fragment_shader = shader._fragment_shader;
    _shader_program = shader._shader_program;
    _param_loc_cache = shader._param_loc_cache;
}

Shader::Shader(const char *vert_src, const char *frag_src)
{
    _ref_count = new int;
    *_ref_count = 1;

    if (addVertexShaderSource(vert_src) && addFragmentShaderSource(frag_src))
        createShader();
}

Shader &Shader::operator = (const Shader &shader)
{
    *_ref_count -= 1;

    if (_ref_count == 0)
    {
        if ((int)_fragment_shader != -1)
            glDeleteShader(_fragment_shader);
        
        if ((int)_vertex_shader != -1)
            glDeleteShader(_vertex_shader);

        if ((int)_shader_program != -1)
            glDeleteProgram(_shader_program);
    }

    _ref_count = shader._ref_count;
    *_ref_count += 1;

    _vertex_shader = shader._vertex_shader;
    _fragment_shader = shader._fragment_shader;
    _shader_program = shader._shader_program;
    _param_loc_cache = shader._param_loc_cache;

    return *this; 
}

bool Shader::addVertexShaderSource(const char *src)
{
    if ((int)_vertex_shader != -1)
        glDeleteShader(_vertex_shader);
    
    _vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertex_shader, 1, &src, nullptr);
    glCompileShader(_vertex_shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(_vertex_shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(_vertex_shader, 512, nullptr, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
        _vertex_shader = -1;
        return false;
    }

    return true;
}

bool Shader::addFragmentShaderSource(const char *src)
 {
    if ((int)_fragment_shader != -1)
        glDeleteShader(_fragment_shader);
    
    _fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragment_shader, 1, &src, nullptr);
    glCompileShader(_fragment_shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(_fragment_shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(_fragment_shader, 512, nullptr, infoLog);
        printf("ERROR::SHADER::Fragment::COMPILATION_FAILED\n%s", infoLog);
        _fragment_shader = -1;
        return false;
    }

    return true;
 }

bool Shader::createShader()
{
    if ((int)_shader_program != -1)
        glDeleteProgram(_shader_program);

    _shader_program = glCreateProgram();

    glAttachShader(_shader_program, _vertex_shader);
    glAttachShader(_shader_program, _fragment_shader);
    glLinkProgram(_shader_program);

    int success;
    char infoLog[512];

    glGetProgramiv(_shader_program, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(_shader_program, 512, NULL, infoLog);
        printf("ERROR::SHADER::LINKING_FAILED\n%s", infoLog);
        _shader_program = -1;
        return false;
    }

    return true;
}

 Shader::~Shader() 
 {
    if ((int)_fragment_shader != -1)
        glDeleteShader(_fragment_shader);
    
    if ((int)_vertex_shader != -1)
        glDeleteShader(_vertex_shader);

    if ((int)_shader_program != -1)
        glDeleteProgram(_shader_program);
 }