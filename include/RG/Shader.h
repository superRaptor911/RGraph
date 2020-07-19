#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace rg
{
    typedef unsigned int uint;

    class Shader
    {
    private:
        uint _vertex_shader = -1;
        uint _fragment_shader = -1;
        uint _shader_program = -1;

    public:
        Shader();

        bool addVertexShaderSource(const char *src);
        bool addFragmentShaderSource(const char *src);
        bool createShader();

        bool makeShader();
        ~Shader();
    };    
}

#endif
