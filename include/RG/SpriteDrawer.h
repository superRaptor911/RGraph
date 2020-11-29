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
