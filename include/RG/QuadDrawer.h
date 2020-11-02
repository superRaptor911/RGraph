#ifndef QUAD_DRAWER_H
#define QUAD_DRAWER_H

#include <RG/Global_Def.h>
#include <RG/Quad.h>
#include <RG/Shader.h>

namespace rg
{
    class Window;

    class QuadDrawer
    {

        const float m_Vertex_data[8] = {
            // positions         // texture coords
             0.f,   1.f,
             1.f,   1.f,
             1.f,   0.f,
             0.f,   0.f
        };

        const uint m_Indices[6] = {
            0, 1, 2, // first triangle
            2, 3, 0  // second triangle
        };

        uint m_VAO;
        uint  m_VBO, m_EBO;

        Shader m_shader;

        Window *m_window = nullptr;

            
    private:

        void m_Init();

    public:

        QuadDrawer(Window *window);
        void drawQuad(Quad &quad);

    };
    
} // namespace rg


#endif
