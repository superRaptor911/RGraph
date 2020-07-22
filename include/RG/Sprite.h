#ifndef SPRITE_H
#define SPRITE_H

#include <RG/Texture.h>
#include <RG/Shader.h>
#include <RG/Ref_Base.h>

namespace rg
{
    class Sprite : public Ref_Base
    {
    private:

        Texture _texture;
        glm::vec2 _scale = glm::vec2(1.f, 1.f);
        // Position of sprite
        glm::vec2 _position;
        // Origin of sprite
        glm::vec2 _origin;

        uint _VAO, _VBO, _EBO;

        inline static const float _vertex_data[] = {
            // positions         // texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
        };

        inline static const uint _indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

    private:

        inline void _decrementRefCount();

    public:

        Sprite();

        Sprite(const Texture &T);

        Sprite(const Sprite &S);

        Sprite &operator = (const Sprite &S);

        Texture getTexture() const {return _texture;}

        void setTexture(const Texture &T) {_texture = T;}

        glm::vec2 getPosition() const {return _position;}

        void setPosition(const glm::vec2 &pos) {_position = pos;}

        glm::vec2 getOrigin() const {return _origin;}

        void setOrigin(const glm::vec2 &origin) {_origin = origin;}

        void draw();

        ~Sprite();
    };
    
}

#endif
