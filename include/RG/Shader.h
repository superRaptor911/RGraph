#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <RG/Color.h>

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

    private:

        inline int _getUniformLocation(const std::string &param);
        inline void _decrementRefCount();
    
    public:

        static Shader DefaultShader;

    public:
        Shader();
        Shader(const Shader &shader);
        Shader(const char *vert_src, const char *frag_src);

        Shader &operator = (const Shader &shader);

        bool addVertexShaderSource(const char *src);
        bool addFragmentShaderSource(const char *src);
        bool createShader();

        void setParam(const std::string &param, int val);
        void setParam(const std::string &param, float val);
        void setParam(const std::string &param, const glm::vec2 &val);
        void setParam(const std::string &param, const glm::vec3 &val);
        void setParam(const std::string &param, const glm::vec4 &val);
        void setParam(const std::string &param, const Color &val);

        void useShader();

        ~Shader();
    };
}

#endif
