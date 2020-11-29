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
