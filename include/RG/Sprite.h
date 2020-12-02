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

        Sprite(const Texture &texture);

        void setTexture(const Texture &texture);

        Texture getTexture();

    };    
}

#endif
