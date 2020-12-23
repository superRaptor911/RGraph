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
	float m_Uvs[8] = {
        //UVS 
            0.f,   0.f,
            1.f,   0.f,
            1.f,   1.f,
            0.f,   1.f,
	};


        friend SpriteDrawer;

    public:

        Sprite() { m_color = Color::White;};

        Sprite(const Texture &texture);

        void setTexture(const Texture &texture);

        Texture getTexture();

    };    
}

#endif
