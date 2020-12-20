#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <RG/Color.h>
#include <RG/Ref_Base.h>

namespace rg
{
    class Shader : public Ref_Base
    {
    private:
        uint m_vertex_shader = RG_INVALID_ID;
        uint m_fragment_shader = RG_INVALID_ID;
        uint m_shader_program = RG_INVALID_ID;

        std::unordered_map<std::string, int> m_param_loc_cache;

    private:

        inline int m_getUniformLocation(const std::string &param);
        inline void m_decrementRefCount();
        bool m_chkShaderError(uint &id);
	bool m_chkProgramError(uint &id);
    

    public:
        Shader();
        Shader(const Shader &shader);
        Shader(const std::string &vert_src, const std::string &frag_src);

        Shader &operator = (const Shader &shader);

        bool createShader(const std::string &vert_src, const std::string &frag_src);

        void setParam(const std::string &param, int val);
        void setParam(const std::string &param, float val);
        void setParam(const std::string &param, const glm::vec2 &val);
        void setParam(const std::string &param, const glm::vec3 &val);
        void setParam(const std::string &param, const glm::vec4 &val);
        void setParam(const std::string &param, const glm::mat4 &val);
        void setParam(const std::string &param, const Color &val);

        void activate();

        ~Shader();
    };
}

#endif
