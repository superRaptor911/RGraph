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
    attachRefCount(shader);

    m_vertex_shader = shader.m_vertex_shader;
    m_fragment_shader = shader.m_fragment_shader;
    m_shader_program = shader.m_shader_program;
    m_param_loc_cache = shader.m_param_loc_cache;
    
}

Shader::Shader(const std::string &vert_src, const std::string &frag_src)
{
    startRefCounting();

    if (!createShader(vert_src, frag_src))
        printf("Error : Failed to create shader\n");
}

Shader &Shader::operator = (const Shader &shader)
{
    m_decrementRefCount();
    attachRefCount(shader);

    m_vertex_shader = shader.m_vertex_shader;
    m_fragment_shader = shader.m_fragment_shader;
    m_shader_program = shader.m_shader_program;
    m_param_loc_cache = shader.m_param_loc_cache;

    return *this; 
}

bool Shader::m_chkShaderError(uint &id)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(id, 1024, NULL, infoLog);
        printf("SHADER-ERROR::\n%s \n", infoLog);
        id = RG_INVALID_ID;
	return false;
    } 

    return true;
}

bool Shader::m_chkProgramError(uint &id)
{
    GLint status;
    glGetProgramiv (id, GL_LINK_STATUS, &status);

    if (!status)
    {
        GLint infoLogLength;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(id, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
	return false;
    }
    return true;
}


bool Shader::createShader(const std::string &vert_src, const std::string &frag_src)
{
    // Delete program if already exists
    if (m_shader_program != RG_INVALID_ID)
        glDeleteProgram(m_shader_program);

    const char *v_src = vert_src.c_str();
    m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertex_shader, 1, &v_src, nullptr);
    glCompileShader(m_vertex_shader);
    if (!m_chkShaderError(m_vertex_shader))
    {
	printf("Error: Failed to compile vertex shader.\n");
	return false;
    }

    const char* f_src = frag_src.c_str();
    m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragment_shader, 1, &f_src, nullptr);
    glCompileShader(m_fragment_shader);
    if (!m_chkShaderError(m_fragment_shader))
    {
	printf("Error: Failed to compile fragment shader.\n");
	return false;
    }
    
    m_shader_program = glCreateProgram();
    glAttachShader(m_shader_program, m_vertex_shader);
    glAttachShader(m_shader_program, m_fragment_shader);
    glLinkProgram(m_shader_program);

    return m_chkProgramError(m_shader_program);
}

int Shader::m_getUniformLocation(const std::string &param)
{
    // Set as current shader
    glUseProgram(m_shader_program);
    // Search cache first
    auto it = m_param_loc_cache.find(param);
    if (it != m_param_loc_cache.end())
        return it->second;

    // Get location
    int uniform_loc = glGetUniformLocation(m_shader_program, param.c_str());
    // Check validity of location
    if (uniform_loc == -1)
    {
        printf("Error: Uniform %s not found\n", param.c_str());
        return uniform_loc;
    }

    // Add to cache
    m_param_loc_cache.insert(std::pair<std::string, int>(param, uniform_loc));

    return uniform_loc;
}

void Shader::setParam(const std::string &param, int val)
{
    int loc = m_getUniformLocation(param);

    if (loc != -1)
        glUniform1i(loc, val);
}


void Shader::setParam(const std::string &param, float val)
{
    int loc = m_getUniformLocation(param);

    if (loc != -1)
        glUniform1f(loc, val);
}

void Shader::setParam(const std::string &param, const glm::vec2 &val)
{
    int loc = m_getUniformLocation(param);

    if (loc != -1)
        glUniform2f(loc, val.x, val.y);
}

void Shader::setParam(const std::string &param, const glm::vec3 &val)
{
    int loc = m_getUniformLocation(param);

    if (loc != -1)
        glUniform3f(loc, val.x, val.y, val.z);
}

void Shader::setParam(const std::string &param, const glm::vec4 &val)
{
    int loc = m_getUniformLocation(param);

    if (loc != -1)
        glUniform4f(loc, val.x, val.y, val.z, val.a);
}


void Shader::setParam(const std::string &param, const glm::mat4 &val)
{
    int loc = m_getUniformLocation(param);

    if (loc != -1)
        glUniformMatrix4fv(loc, 1, GL_FALSE, &val[0][0]);
}

void Shader::setParam(const std::string &param, const Color &val)
{
    int loc = m_getUniformLocation(param);

    if (loc != -1)
        glUniform4f(loc, val.r, val.g, val.b, val.a);
}

void Shader::m_decrementRefCount()
{
    // Free resource if reference count is 1
    if (dettachRefCount())
    {
        if (m_fragment_shader != RG_INVALID_ID)
            glDeleteShader(m_fragment_shader);
        
        if (m_vertex_shader != RG_INVALID_ID)
            glDeleteShader(m_vertex_shader);

        if (m_shader_program != RG_INVALID_ID)
            glDeleteProgram(m_shader_program);
    }
}

void Shader::activate()
{
    glUseProgram(m_shader_program);
}

Shader::~Shader() 
{
    m_decrementRefCount();
}
