#ifndef SPRITEBATCHER_H
#define SPRITEBATCHER_H

#include <vector>
#include <RG/Sprite.h>
#include <map>


namespace rg
{
    class SpriteBatcher
    {
    private:
        
        std::vector<Sprite> _draw_queue;

        std::map<uint, std::vector<Sprite>> _texture_map;

        std::vector<int> _batches;

        // opengl vertex array obj 
        uint _VAO;
        // Buffers
        uint  _VBO, _EBO, _trans_buffer, _tex_id_buffer;

        const float _vertex_data[16] = {
            // positions         // texture coords
             0.f,   1.f,   1.0f, 1.0f, // top right
             1.f,   1.f,   0.0f, 1.0f, // bottom right
             1.f,   0.f,   0.0f, 0.0f, // bottom left
             0.f,   0.f,   1.0f, 0.0f  // top left 
        };

        const uint _indices[6] = {
            0, 1, 2, // first triangle
            2, 3, 0  // second triangle
        };

        Shader _default_shader;

        static SpriteBatcher _SBinstance;

        const int _max_sprites_per_batch = 10000;
        int _max_textures_per_batch = 16;

    private:

        SpriteBatcher();

        static void _drawAllSprites();

        static void _initBatcher();

    public:

        static void addSprite(const Sprite &spr) { _SBinstance._draw_queue.push_back(spr);}

        ~SpriteBatcher() {}
    };    
}

#endif
