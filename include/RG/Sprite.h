#ifndef SPRITE_H
#define SPRITE_H

#include <RG/Texture.h>
#include <RG/Shader.h>
#include <RG/Global_Def.h>

namespace rg
{
    class Sprite
    {
    private:

        int _ref_count;
        Texture _texture;
        glm::vec2 _scale = glm::vec2(1.f, 1.f);
        // Position of sprite
        glm::vec2 _position;
        // Origin of sprite
        glm::vec2 _origin;

        uint _VA0, _VBO, _IBO;

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
