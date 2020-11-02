#include <RG/QuadBatcher.h>
#include <RG/deps/glad/glad.h>
#include <RG/deps/GLFW/glfw3.h>
#include <RG/Window.h>

using namespace rg;

QuadBatcher::QuadBatcher(Window *window)
{
    m_window = window;

    const char *vertex_source = "#version 330 core\n"
                                "layout (location = 0) in vec2 vpos;\n"
                                "layout (location = 1) in vec4 instanceColor;\n"
                                "layout (location = 2) in mat4 instanceMatrix;\n"

                                "out vec4 clr;\n"

                                "uniform mat4 proj;\n"

                                "void main()\n"
                                "{\n"
                                    " gl_Position = proj * instanceMatrix * vec4(vpos, 0.0, 1.0);\n"
                                    "clr = instanceColor;\n"
                                "}\n";
    
    const char *frag_source  = "#version 330 core\n"
                                "out vec4 FragColor;\n"

                                "in vec4 clr;\n"

                                "void main()\n"
                                "{\n"
                                "	FragColor = clr;\n"
                                "}\n";
    

    m_shader.addVertexShaderSource(vertex_source);
    m_shader.addFragmentShaderSource(frag_source);
    m_shader.createShader();

    int size_of_vertex = sizeof(float) * (2); // 2 floats for pos

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    glGenBuffers(1, &m_trans_buffer);
    glGenBuffers(1, &m_color_buffer);

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

    // Trans buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_trans_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_Max_Units * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
    std::size_t vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(2); 
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(3); 
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(4); 
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(5); 
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
}


void QuadBatcher::draw(std::vector<Quad> &quads)
{
    int quad_count = quads.size();
    std::vector<glm::mat4> transforms(quad_count);
    std::vector<glm::vec4> colors(quad_count);

    int id = 0;
    for (auto &i : quads)
    {
        transforms[id] = i.getTransformMatrix();
        auto color = i.getColor();
        colors[id] = glm::vec4(color.r, color.g, color.b, color.a);
        id++;
    }

    int batch_count = (quad_count - 1) / m_Max_Units + 1;
    int quads_remaining = quad_count;

    m_shader.activate();
    m_shader.setParam("proj", m_window->getOrthoProjection());

    for (int i = 0; i < batch_count; i++)
    {
        int count = std::min(m_Max_Units, quads_remaining);
        quads_remaining -= count;

        // Transform buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_trans_buffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(glm::mat4), &transforms[i * m_Max_Units]);
        
        // Color buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_color_buffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(glm::vec4), &colors[i * m_Max_Units]);
        
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, count);
    }
}