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
        glm::vec2 _position = glm::vec2(0,0);
        // Origin of sprite
        glm::vec2 _origin  = glm::vec2(0,0);
        // Rotation of sprite
        float _rotation = 0.f;

        uint _VAO, _VBO, _EBO;

        Shader _custom_shader;

        inline static const float _vertex_data[] = {
            // positions         // texture coords
             1.f,   1.f,   1.0f, 1.0f, // top right
             1.f,   0.f,   1.0f, 0.0f, // bottom right
             0.f,   0.f,   0.0f, 0.0f, // bottom left
             0.f,   1.f,   0.0f, 1.0f  // top left 
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

        void setTexture(const Texture &T) {_texture = T; _origin = glm::vec2(T.getSize()) / 2.f;}

        glm::vec2 getPosition() const {return _position;}

        void setPosition(const glm::vec2 &pos) {_position = pos;}

        void move(const glm::vec2 &delta) { _position += delta;}

        glm::vec2 getOrigin() const {return _origin;}

        void setOrigin(const glm::vec2 &origin) {_origin = origin;}

        glm::vec2 getScale() { return _scale;}

        void setScale(const glm::vec2 &scale) { _scale = scale;}

        float getRotaion() { return _rotation;}

        void setRotation(float rot) { _rotation = rot;}

        void rotate(float angle) { _rotation += angle;}

        void draw();

        ~Sprite();
    };
    
}

#endif
