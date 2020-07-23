#include <RG/Shader.h>
#include <RG/r_util.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace rg;

Shader::Shader()
{
    startRefCounting();
}

Shader::Shader(const Shader &shader)
{
    attachToRefCount(shader);

    _vertex_shader = shader._vertex_shader;
    _fragment_shader = shader._fragment_shader;
    _shader_program = shader._shader_program;
    _param_loc_cache = shader._param_loc_cache;
}

Shader::Shader(const char *vert_src, const char *frag_src)
{
    startRefCounting();

    if (addVertexShaderSource(vert_src) && addFragmentShaderSource(frag_src))
        createShader();
}

Shader &Shader::operator = (const Shader &shader)
{
    _decrementRefCount();
    attachToRefCount(shader);

    _vertex_shader = shader._vertex_shader;
    _fragment_shader = shader._fragment_shader;
    _shader_program = shader._shader_program;
    _param_loc_cache = shader._param_loc_cache;

    return *this; 
}

bool Shader::_chkError(uint &id, const std::string &type)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(id, 1024, NULL, infoLog);
        printf("ERROR:: %s shader.\n%s----------------\n", type.c_str() ,infoLog);

        if (type == "Linking")
            glDeleteProgram(id);
        else
            glDeleteShader(id);
        
        id = RG_INVALID_ID;
    }

    return success;
}

bool Shader::addVertexShaderSource(const char *src)
{
    // Delete shader if already exists
    if (_vertex_shader != RG_INVALID_ID)
        glDeleteShader(_vertex_shader);
    
    // create new shader
    _vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertex_shader, 1, &src, nullptr);
    glCompileShader(_vertex_shader);

    return _chkError(_vertex_shader, "Vertex");
}

bool Shader::addFragmentShaderSource(const char *src)
 {
    // Delete shader if already exists
    if (_fragment_shader != RG_INVALID_ID)
        glDeleteShader(_fragment_shader);

    _fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragment_shader, 1, &src, nullptr);
    glCompileShader(_fragment_shader);

    return _chkError(_fragment_shader, "Fragment");
 }

bool Shader::createShader()
{
    // Delete program if already exists
    if (_shader_program != RG_INVALID_ID)
        glDeleteProgram(_shader_program);

    _shader_program = glCreateProgram();

    glAttachShader(_shader_program, _vertex_shader);
    glAttachShader(_shader_program, _fragment_shader);
    glLinkProgram(_shader_program);

    return _chkError(_shader_program, "Linking");
}

int Shader::_getUniformLocation(const std::string &param)
{
    // Set as current shader
    glUseProgram(_shader_program);
    // Search cache first
    auto it = _param_loc_cache.find(param);
    if (it != _param_loc_cache.end())
        return it->second;

    DEBUG_PRINT("shader Cache miss");

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
    // Free resource if reference count is 1
    if (dettachRefCount())
    {
        if (_fragment_shader != RG_INVALID_ID)
            glDeleteShader(_fragment_shader);
        
        if (_vertex_shader != RG_INVALID_ID)
            glDeleteShader(_vertex_shader);

        if (_shader_program != RG_INVALID_ID)
            glDeleteProgram(_shader_program);
        
        DEBUG_PRINT("Deleting shader");
    }
}

void Shader::activate()
{
    glUseProgram(_shader_program);
}

Shader::~Shader() 
{
    _decrementRefCount();
}