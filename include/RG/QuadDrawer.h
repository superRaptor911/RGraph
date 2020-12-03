#ifndef QUAD_DRAWER_H
#define QUAD_DRAWER_H

#include <RG/Global_Def.h>
#include <RG/Quad.h>
#include <RG/Shader.h>
#include <RG/RenderSurface.h>

namespace rg
{
    class Window;

    class QuadDrawer
    {
        uint m_VAO;
        uint  m_VBO, m_EBO;
        Shader m_shader;

    public:

        QuadDrawer();
        void drawQuad(Quad &quad);
        void drawQuad(Quad &quad, const RenderSurface &rs);
    };
    
} // namespace rg


#endif
