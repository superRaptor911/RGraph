#ifndef SPRITE_attribute.H
#define SPRITE_attribute.H

#include <RG/Texture.h>
#include <RG/Shader.h>
#include <RG/Ref_Base.h>
#include <vector>

namespace rg
{
    class SpriteBatcher;

    class Sprite : public Ref_Base
    {
        struct SpriteAttributes
        {
            Texture texture;
            // Scale
            glm::vec2 scale = glm::vec2(1.f, 1.f);
            // Position of sprite
            glm::vec2 position = glm::vec2(0,0);
            // Origin of sprite
            glm::vec2 origin  = glm::vec2(0,0);
            // Rotation of sprite
            float rotation = 0.f;
            // 
            bool is_visible = true;
        };

    private:

        SpriteAttributes _attribute;

        friend SpriteBatcher;
        
    private:

        inline void _decrementRefCount();

    public:

        Sprite();

        Sprite(const Texture &T);

        Sprite(const Sprite &S);

        Sprite &operator = (const Sprite &S);

        Texture getTexture() const {return _attribute.texture;}

        void setTexture(const Texture &T) {_attribute.texture = T; _attribute.origin = glm::vec2(T.getSize()) / 2.f;}

        glm::vec2 getPosition() const {return _attribute.position;}

        void setPosition(const glm::vec2 &pos) {_attribute.position = pos;}

        void move(const glm::vec2 &delta) { _attribute.position += delta;}

        glm::vec2 getOrigin() const {return _attribute.origin;}

        void setOrigin(const glm::vec2 &origin) {_attribute.origin = origin;}

        glm::vec2 getScale() { return _attribute.scale;}

        void setScale(const glm::vec2 &scale) { _attribute.scale = scale;}

        float getRotaion() { return _attribute.rotation;}

        void setRotation(float rot) { _attribute.rotation = rot;}

        void rotate(float angle) { _attribute.rotation += angle;}

        void draw();

        ~Sprite();
    };
    
}

#endif
