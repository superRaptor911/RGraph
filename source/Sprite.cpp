#include <RG/Sprite.h>

using namespace rg;

Sprite::Sprite(const Texture &texture)
{
    setTexture(texture);
}


void Sprite::setTexture(const Texture &texture)
{
    m_texture = texture;
    m_size = texture.getSize();
    m_transformation_changed = true;
}


Texture Sprite::getTexture()
{
    return m_texture;
}

