#ifndef SPRITE_H
#define SPRITE_H

#include <RG/Quad.h>
#include <RG/Texture.h>

namespace rg
{
    class SpriteDrawer;

    class Sprite : public Quad
    {
    private:

        Texture m_texture;

        friend SpriteDrawer;

    public:

        Sprite() { m_color = Color::White;};

        Sprite(Texture &texture);

        void setTexture(Texture &texture);

        Texture getTexture();

    };    
}

#endif
