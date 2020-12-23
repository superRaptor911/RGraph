#include <RG/SpriteDrawer.h>
#include <RG/RGraph.h>

using namespace rg;

SpriteDrawer::SpriteDrawer()
{
    const float m_Vertex_data[8] = {
        // positions 
            0.f,   1.f,
            1.f,   1.f,
            1.f,   0.f,
            0.f,   0.f,
    };

    const uint m_Indices[6] = {
        0, 1, 2, // first triangle
        2, 3, 0  // second triangle
    };

    int vertex_size = sizeof(float) * 2;

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    glGenBuffers(1, &m_UVs);

    glBindVertexArray(m_VAO);

    // position attribute
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * vertex_size, m_Vertex_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), m_Indices, GL_STATIC_DRAW);

    // UV data, Tex coords
    glBindBuffer(GL_ARRAY_BUFFER, m_UVs);
    glBufferData(GL_ARRAY_BUFFER, 4 * vertex_size, m_Vertex_data, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    static const std::string vertex_source = "#version 330 core\n"
                                "layout (location = 0) in vec2 vpos;\n"
                                "layout (location = 1) in vec2 UVs;\n"
                                "out vec2 uv;\n"

                                "uniform mat4 proj;\n"
                                "uniform mat4 model;\n"

                                "void main()\n"
                                "{\n"
                                    " gl_Position = proj * model * vec4(vpos.xy, 0.0, 1.0);\n"
                                    " uv = UVs;\n"
                                "}\n";
    
    static const std::string frag_source = "#version 330 core\n"
                            "out vec4 FragColor;\n"
                            "in vec2 uv;\n"

                            "uniform vec4 color;\n"
                            "uniform sampler2D tex;\n"

                            "void main()\n"
                            "{\n"
                            "	FragColor = texture(tex, uv) * color;\n"
                            "}\n";
    
    static const Shader shader(vertex_source, frag_source);
    m_shader = shader;
}


void SpriteDrawer::drawSprite(Sprite &sprite)
{
    m_shader.activate();
    m_shader.setParam("proj", RGraph::getInstancePtr()->getDefaultWindow()->getOrthoProjection());
    m_shader.setParam("model", sprite.getTransformMatrix());
    m_shader.setParam("color", sprite.m_color);
    sprite.m_texture.activate();

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_UVs);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(float), &sprite.m_Uvs);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void SpriteDrawer::drawSprite(Sprite &sprite, const glm::mat4 &surfaceTransform)
{
    m_shader.activate();
    m_shader.setParam("proj", surfaceTransform);
    m_shader.setParam("model", sprite.getTransformMatrix());
    m_shader.setParam("color", sprite.m_color);
    sprite.m_texture.activate();

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_UVs);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(float), &sprite.m_Uvs);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void SpriteDrawer::drawSprite(Sprite &sprite, Shader &shader)
{
    shader.activate();
    sprite.m_texture.activate();
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_UVs);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(float), &sprite.m_Uvs);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

