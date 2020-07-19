#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace rg
{
    typedef unsigned int uint;

    class Shader
    {
    private:
        uint _vertex_shader;
        uint _fragment_shader;

    public:
        Shader();

        bool addVertexShaderSource(const std::string &src);
        bool addFragmentShaderSource(const std::string &src);

        bool makeShader();
        ~Shader();
    };    
}

#endif
