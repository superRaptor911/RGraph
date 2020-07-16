#ifndef SPRITE_H
#define SPRITE_H

#include <RG/Texture.h>

namespace rg
{
    class Sprite
    {
    private:

        Texture _texture;

        glm::vec2 _scale = glm::vec2(1.f, 1.f);

        glm::vec2 _position;

    public:

        Sprite() {};

        Sprite(const Texture &T);

        void setTexture(const Texture &T);

        void draw();

        ~Sprite() {};
    };
    
}

#endif
