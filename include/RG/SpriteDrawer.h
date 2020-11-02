#ifndef SPRITEDRAWER_H
#define SPRITEDRAWER_H

#include <RG/Global_Def.h>
#include <RG/Sprite.h>
#include <RG/Shader.h>

namespace rg
{
    class Window;
    class SpriteDrawer
    {
    private:

        const float m_Vertex_data[16] = {
            // positions         // texture coords
             0.f,   1.f,   1.0f, 1.0f, // top right
             1.f,   1.f,   0.0f, 1.0f, // bottom right
             1.f,   0.f,   0.0f, 0.0f, // bottom left
             0.f,   0.f,   1.0f, 0.0f  // top left 
        };

        const uint m_Indices[6] = {
            0, 1, 2, // first triangle
            2, 3, 0  // second triangle
        };

        uint m_VAO;
        uint  m_VBO, m_EBO;

        Shader m_shader;

        Window *m_window = nullptr;


    public:
        SpriteDrawer(Window *window);
        void drawSprite(Sprite &sprite);
    };
}

#endif
