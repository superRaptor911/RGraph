#ifndef SPRITEBATCHER_H
#define SPRITEBATCHER_H

#include <RG/Shader.h>
#include <RG/Sprite.h>
#include <vector>


namespace rg
{
    class SpriteBatcher
    {
        uint m_VAO;
        uint  m_VBO, m_EBO, m_trans_buffer, m_color_buffer, m_texID_buffer;

        Shader m_shader;

        const int m_Max_Units = 10000;
        int m_max_texture_per_batch = 1;


        const float m_vertex_data[8] = {
            // positions   
             0.f,   1.f,
             1.f,   1.f, 
             1.f,   0.f,
             0.f,   0.f,
        };

        const uint m_indices[6] = {
            0, 1, 2, // first triangle
            2, 3, 0  // second triangle
        };

    private:
    
    public:

        SpriteBatcher();

        void draw(std::vector<Sprite> &sprites);

    };
    
}

#endif
