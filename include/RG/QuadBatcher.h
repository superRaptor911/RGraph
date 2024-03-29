#ifndef QUADBATCHER_H
#define QUADBATCHER_H

#include "glm/fwd.hpp"
#include <RG/Global_Def.h>
#include <RG/Shader.h>
#include <RG/Quad.h>
#include <vector>

namespace rg
{
    class Window;
    class QuadBatcher
    {
        uint m_VAO;
        uint  m_VBO, m_EBO, m_trans_buffer, m_color_buffer;

        Shader m_shader;
	
	// Maximum quads to be drawn in 1 draw call
        const int m_Max_Units = 10000;

        const float m_vertex_data[8] = {
            // positions
             0.f,   1.f,
             1.f,   1.f,
             1.f,   0.f,
             0.f,   0.f,
        };

        const uint m_indices[6] = {
            0, 1, 2, // first triangle
            2, 3, 0  // second triangle
        };


    private:

    public:

        QuadBatcher();
        void draw(std::vector<Quad> &quads);
        void draw(std::vector<Quad> &quads, const glm::mat4 &surfaceTransform);
    };   
}

#endif
