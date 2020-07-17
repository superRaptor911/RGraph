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

        glm::vec2 _origin;

    public:

        Sprite() {};

        Sprite(const Texture &T);

        Texture getTexture() const {return _texture;}

        void setTexture(const Texture &T) {_texture = T;}

        glm::vec2 getPosition() const {return _position;}

        void setPosition(const glm::vec2 &pos) {_position = pos;}

        glm::vec2 getOrigin() const {return _origin;}

        void setOrigin(const glm::vec2 &origin) {_origin = origin;}

        void draw();

        ~Sprite() {};
    };
    
}

#endif
