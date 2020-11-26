#include <RG/SpriteDrawer.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <RG/Window.h>

using namespace rg;

SpriteDrawer::SpriteDrawer(Window *window)
{
    m_window = window;


    int vertex_size = sizeof(float) * 4;

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    // position attribute
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * vertex_size, m_Vertex_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), m_Indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    std::string vertex_source = "#version 420 core\n"
                                "layout (location = 0) in vec2 vpos;\n"
                                "layout (location = 1) in vec2 texCoord;\n"
                                "out vec2 uv;\n"

                                "uniform mat4 proj;\n"
                                "uniform mat4 model;\n"

                                "void main()\n"
                                "{\n"
                                    " gl_Position = proj * model * vec4(vpos, 0.0, 1.0);\n"
                                    " uv = texCoord;\n"
                                "}\n";
    
    std::string frag_source = "#version 420 core\n"
                            "out vec4 FragColor;\n"
                            "in vec2 uv;\n"

                            "uniform vec4 color;\n"
                            "uniform sampler2D tex;\n"

                            "void main()\n"
                            "{\n"
                            "	FragColor = texture(tex, uv) * color;\n"
                            "}\n";
    
    m_shader.addVertexShaderSource(vertex_source);
    m_shader.addFragmentShaderSource(frag_source);
    m_shader.createShader();// = Shader(vertex_source, frag_source);
}


void SpriteDrawer::drawSprite(Sprite &sprite)
{
    m_shader.activate();
    m_shader.setParam("proj", m_window->getOrthoProjection());
    m_shader.setParam("model", sprite.getTransformMatrix());
    m_shader.setParam("color", sprite.m_color);
    sprite.m_texture.activate();

    //printf("(%f, %f)\n", sprite.m_size.x, sprite.m_size.y);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
