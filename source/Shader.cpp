#include <RG/Shader.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define Testing

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
    _decrementRefCount();

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
    if (_vertex_shader != RG_INVALID_ID)
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
        _vertex_shader = RG_INVALID_ID;
        return false;
    }

    return true;
}

bool Shader::addFragmentShaderSource(const char *src)
 {
    if (_fragment_shader != RG_INVALID_ID)
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
        _fragment_shader = RG_INVALID_ID;
        return false;
    }

    return true;
 }

bool Shader::createShader()
{
    if (_shader_program != RG_INVALID_ID)
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
        _shader_program = RG_INVALID_ID;
        return false;
    }

    return true;
}

int Shader::_getUniformLocation(const std::string &param)
{
    // Search cache first
    auto it = _param_loc_cache.find(param);
    if (it != _param_loc_cache.end())
        return it->second;

    #ifdef Testing
        printf("Cache miss\n");
    #endif

    // Get location
    int uniform_loc = glGetUniformLocation(_shader_program, param.c_str());
    // Check validity of location
    if (uniform_loc == -1)
    {
        printf("Error: Uniform %s not found", param.c_str());
        return uniform_loc;
    }

    // Add to cache
    _param_loc_cache.insert(std::pair<std::string, int>(param, uniform_loc));

    return uniform_loc;
}

void Shader::setParam(const std::string &param, int val)
{
    int loc = _getUniformLocation(param);

    if (loc != -1)
        glUniform1i(loc, val);
}


void Shader::setParam(const std::string &param, float val)
{
    int loc = _getUniformLocation(param);

    if (loc != -1)
        glUniform1f(loc, val);
}

void Shader::setParam(const std::string &param, const glm::vec2 &val)
{
    int loc = _getUniformLocation(param);

    if (loc != -1)
        glUniform2f(loc, val.x, val.y);
}

void Shader::setParam(const std::string &param, const glm::vec3 &val)
{
    int loc = _getUniformLocation(param);

    if (loc != -1)
        glUniform3f(loc, val.x, val.y, val.z);
}

void Shader::setParam(const std::string &param, const glm::vec4 &val)
{
    int loc = _getUniformLocation(param);

    if (loc != -1)
        glUniform4f(loc, val.x, val.y, val.z, val.a);
}

void Shader::setParam(const std::string &param, const Color &val)
{
    int loc = _getUniformLocation(param);

    if (loc != -1)
        glUniform4f(loc, val.r, val.g, val.b, val.a);
}

void Shader::_decrementRefCount()
{
    // reduce count by 1
    *_ref_count -= 1;

    // Free resource if reference count is 1
    if (_ref_count == 0)
    {
        if (_fragment_shader != RG_INVALID_ID)
            glDeleteShader(_fragment_shader);
        
        if (_vertex_shader != RG_INVALID_ID)
            glDeleteShader(_vertex_shader);

        if (_shader_program != RG_INVALID_ID)
            glDeleteProgram(_shader_program);
        
        delete _ref_count;
    }
}

void Shader::useShader()
{
    glUseProgram(_shader_program);
}

Shader::~Shader() 
{
    _decrementRefCount();
}