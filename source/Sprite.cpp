#include <RG/Sprite.h>

using namespace rg;

Sprite::Sprite(Texture &texture)
{
    setTexture(texture);
}


void Sprite::setTexture(Texture &texture)
{
    m_texture = texture;
    m_size = texture.getSize();
    m_transformation_changed = true;
}


Texture Sprite::getTexture()
{
    return m_texture;
}

