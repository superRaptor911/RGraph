#include <RG/RGraph.h>
#include <RG/QuadDrawer.h>
#include <RG/Window.h>
#include <RG/r_util.h>
using namespace rg;


QuadDrawer::QuadDrawer()
{
    const float vertex_data[8] = {
        // positions
            0.f,   1.f,
            1.f,   1.f,
            1.f,   0.f,
            0.f,   0.f
    };

    const uint indices[6] = {
        0, 1, 2, // first triangle
        2, 3, 0  // second triangle
    };

    int vertex_size = sizeof(float) * 2;

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    // position attribute
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * vertex_size, vertex_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    std::string vertex_source = "#version 420 core\n"
	"layout (location = 0) in vec2 vpos;\n"
	"uniform mat4 proj;\n"
	"uniform mat4 model;\n"
	"void main()\n"
	"{\n"
	"gl_Position = proj * model * vec4(vpos, 0.0, 1.0);\n"
	"}\n";

    std::string frag_source = "#version 420 core\n"
	"out vec4 FragColor;\n"
	"uniform vec4 color;\n"
	"void main()\n"
	"{\n"
	"FragColor = color;\n"
	"}\n";

    if (!m_shader.createShader(vertex_source, frag_source))   
    {
	R_CPRINT_ERR("Quad shader creation failed.");
    }
}

void QuadDrawer::drawQuad(Quad &quad)
{
    m_shader.activate();
    m_shader.setParam("proj", RGraph::getInstancePtr()->getDefaultWindow()->getOrthoProjection());
    m_shader.setParam("model", quad.getTransformMatrix());
    m_shader.setParam("color", quad.m_color);

    // Activate default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void QuadDrawer::drawQuad(Quad &quad, const RenderSurface &rs)
{
    rs.activate();
    m_shader.activate();
    m_shader.setParam("proj", rs.getOrthoProjection());
    m_shader.setParam("model", quad.getTransformMatrix());
    m_shader.setParam("color", quad.m_color);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);   
}


void QuadDrawer::drawQuad(Quad &quad, const glm::mat4 &surfaceTransform)
{
    m_shader.activate();
    m_shader.setParam("proj", surfaceTransform);
    m_shader.setParam("model", quad.getTransformMatrix());
    m_shader.setParam("color", quad.m_color);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void QuadDrawer::drawQuad(Quad &quad, const glm::mat4 &surfaceTransform, Shader &shader)
{
    // Next Time
}
