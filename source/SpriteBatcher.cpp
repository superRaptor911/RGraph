#include <RG/SpriteBatcher.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <RG/Window.h>
#include <map>

using namespace rg;

SpriteBatcher::SpriteBatcher(Window *window)
{
    m_window = window;

    const char *vertex_source420 = "#version 420 core\n"
                                "layout (location = 0) in vec2 vpos;\n"
                                "layout (location = 1) in vec4 instanceColor;\n"
                                "layout (location = 2) in float texID;\n"
                                "layout (location = 3) in mat4 instanceMatrix;\n"

                                "out vec4 clr;\n"
                                "out float tex_id;\n"

                                "uniform mat4 proj;\n"

                                "void main()\n"
                                "{\n"
                                    " gl_Position = proj * instanceMatrix * vec4(vpos, 0.0, 1.0);\n"
                                    "clr = instanceColor;\n"
                                    "tex_id = texID;\n"
                                "}\n";
    
    const char *frag_source420  = "#version 420 core\n"
                                "out vec4 FragColor;\n"

                                "in vec4 clr;\n"
                                "in float tex_id;\n"
                                "uniform sampler2D textures[%d];\n"

                                "void main()\n"
                                "{\n"
                                "	FragColor = clr * texture(textures[int(tex_id)], uv);\n"
                                "}\n";
    
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_max_texture_per_batch);
    m_shader.addVertexShaderSource(vertex_source420);
    m_shader.addFragmentShaderSource(frag_source420);
    m_shader.createShader();

    int size_of_vertex = sizeof(float) * (2); // 2 floats for pos

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    glGenBuffers(1, &m_trans_buffer);
    glGenBuffers(1, &m_color_buffer);
    glGenBuffers(1, &m_texID_buffer);

    glBindVertexArray(m_VAO);

    // position attribute
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * size_of_vertex, m_vertex_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, size_of_vertex, (void*)0);
    glEnableVertexAttribArray(0);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), m_indices, GL_STATIC_DRAW);

    // Color buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_Max_Units * sizeof(glm::vec4), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, size_of_vertex, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);

    // Color buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_texID_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_Max_Units * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);

    // Trans buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_trans_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_Max_Units * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
    std::size_t vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(3); 
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(4); 
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(5); 
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6); 
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
}


void SpriteBatcher::draw(std::vector<Sprite> &sprites)
{
    int sprite_count = sprites.size();

    struct Batch
    {
        Texture tex;
        std::vector<Sprite *> spr_ptr_list;

        Batch *next_batch = nullptr;
    };

    std::map<Texture, Batch> texture_map;

    std::vector<glm::mat4> transforms(sprite_count);
    std::vector<glm::vec4> colors(sprite_count);
    std::vector<int> texIds(sprite_count);

    // Group by texture
    for (auto &i : sprites)
    {
        auto tex_index_it = texture_map.find(i.getTexture());
        if (tex_index_it == texture_map.end())
        {
            Batch b;
            b.tex = i.getTexture();
            tex_index_it = texture_map.insert(std::pair<Texture, Batch>(i.getTexture(), b)).first;
        }

        Batch *ptr = &tex_index_it->second;
        while (ptr)
        {
            if (ptr->spr_ptr_list.size() >= m_Max_Units)
            {
                if (ptr->next_batch)
                {
                    ptr = ptr->next_batch;
                }
                else
                {
                    ptr->next_batch = new Batch;
                    ptr->next_batch->tex = ptr->tex;
                    ptr = ptr->next_batch;
                }               
            }
            else
            {
                ptr->spr_ptr_list.push_back(&i);
                break;
            }            
        }        
    }

    
    
}
