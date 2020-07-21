#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace rg
{
    typedef unsigned int uint;

    class Shader
    {
    private:
        uint _vertex_shader = -1;
        uint _fragment_shader = -1;
        uint _shader_program = -1;

        int *_ref_count = nullptr;

        std::unordered_map<std::string, int> _param_loc_cache;

    public:
        Shader();
        Shader(const Shader &shader);
        Shader(const char *vert_src, const char *frag_src);

        Shader &operator = (const Shader &shader);

        bool addVertexShaderSource(const char *src);
        bool addFragmentShaderSource(const char *src);
        bool createShader();

        void useShader();

        bool setParam(const std::string &param, int val);
        bool setParam(const std::string &param, float val);
        bool setParam(const std::string &param, const glm::vec2 &val);

        ~Shader();
    };    
}

#endif
