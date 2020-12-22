#ifndef SPRITEDRAWER_H
#define SPRITEDRAWER_H

#include "glm/fwd.hpp"
#include <RG/Global_Def.h>
#include <RG/Sprite.h>
#include <RG/Shader.h>
#include <RG/RenderSurface.h>

namespace rg
{
    class Window;
    class SpriteDrawer
    {
    private:
        uint m_VAO;
        uint m_VBO, m_EBO;
	uint m_UVs;

        Shader m_shader;

    public:

        SpriteDrawer();
        void drawSprite(Sprite &sprite);
        void drawSprite(Sprite &sprite, const glm::mat4 &surfaceTransform);
        void drawSprite(Sprite &sprite, const RenderSurface &rs);
    };
}

#endif
