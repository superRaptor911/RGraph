#include <RG/RGraph.h>
#include <RG/QuadDrawer.h>
#include <RG/Window.h>

using namespace rg;


QuadDrawer::QuadDrawer(Window *window)
{
    m_window = window;
    m_Init();
}

void QuadDrawer::m_Init()
{
    int vertex_size = sizeof(float) * 2;

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

    glBindVertexArray(0);


    std::string vertex_source = "#version 420 core\n"
                                "layout (location = 0) in vec2 vpos;\n"

                                "uniform mat4 proj;\n"
                                "uniform mat4 model;\n"

                                "void main()\n"
                                "{\n"
                                " gl_Position = proj * model * vec4(vpos, 0.0, 1.0);\n"
                                "}\n";
    
    std::string frag_source = "#version 420 core\n"
                            "out vec4 FragColor;\n"
                            "uniform vec4 color;\n"

                            "void main()\n"
                            "{\n"
                            "	FragColor = color;\n"
                            "}\n";
    
    m_shader.addVertexShaderSource(vertex_source);
    m_shader.addFragmentShaderSource(frag_source);
    m_shader.createShader();// = Shader(vertex_source, frag_source);
    printf("Called\n");
}


void QuadDrawer::drawQuad(Quad &quad)
{
    m_shader.activate();
    m_shader.setParam("proj", m_window->getOrthoProjection());
    m_shader.setParam("model", quad.getTransformMatrix());
    m_shader.setParam("color", quad.m_color);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}
